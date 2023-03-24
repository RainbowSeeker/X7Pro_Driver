/******************************************************************************
 * Copyright 2020-2021 The Firmament Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "hal/adc/adc.h"

#define ADC_TIMEOUT_MS 5

err_t hal_adc_open(device_t dev, uint16_t oflag)
{
    ASSERT(dev != NULL);

    adc_dev_t adc_dev = (adc_dev_t)dev;

    if (dev->ref_count == 0) {
        adc_dev->ops->enable(adc_dev, ADC_CMD_ENABLE);
    }

    return E_OK;
}

err_t hal_adc_close(device_t dev)
{
    ASSERT(dev != NULL);

    adc_dev_t adc_dev = (adc_dev_t)dev;

    if (dev->ref_count == 0) {
        adc_dev->ops->enable(adc_dev, ADC_CMD_DISABLE);
    }

    return E_OK;
}

size_t hal_adc_read(device_t dev, off_t pos, void* buffer, size_t size)
{
    ASSERT(dev != NULL);

    size_t res = 0;
    adc_dev_t adc_dev = (adc_dev_t)dev;

    if (os_mutex_take(adc_dev->lock, TICKS_FROM_MS(ADC_TIMEOUT_MS)) != E_OK) {
        return 0;
    }

    if (adc_dev->ops->measure(adc_dev, pos, buffer) == E_OK) {
        res = size;
    }

    os_mutex_release(adc_dev->lock);

    return res;
}

err_t hal_adc_register(adc_dev_t adc_dev, const char* name, uint32_t flag, void* data)
{
    err_t ret;
    struct device* device;

    ASSERT(adc_dev != NULL);

    device = &(adc_dev->parent);

    device->type = Device_Class_Char;
    device->ref_count = 0;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = NULL;
    device->open = hal_adc_open;
    device->close = hal_adc_close;
    device->read = hal_adc_read;
    device->write = NULL;
    device->control = NULL;
    device->user_data = data;

    adc_dev->lock = os_mutex_create(name);
    ASSERT(adc_dev->lock != NULL);

    /* register a character device */
    ret = device_register(device, name, flag);

    return ret;
}