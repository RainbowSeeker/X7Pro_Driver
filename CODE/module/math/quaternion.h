
#ifndef QUATERNION_H__
#define QUATERNION_H__

#include <common_def.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float roll;
    float pitch;
    float yaw;
} Euler;

typedef struct {
    float w;
    float x;
    float y;
    float z;
} quaternion;

//__STATIC_INLINE void quaternion_loadIdentity(quaternion * q);
void quaternion_normalize(quaternion* q);
void quaternion_mult(quaternion* result, const quaternion* left, const quaternion* right);
void quaternion_add(quaternion* result, const quaternion* left, const quaternion* right);
void quaternion_rotateVector(const quaternion* rotation, const float from[3], float to[3]);
void quaternion_inv_rotateVector(const quaternion* rotation, const float from[3], float to[3]);
void quaternion_create(quaternion* q, float theta, float axis[3]);
void quaternion_fromTwoQuaternionRotation(quaternion* q, const quaternion* q1, const quaternion* q2);
void quaternion_fromTwoVectorRotation(quaternion* result, const float from[3], const float to[3]);
void quaternion_toEuler(const quaternion* q, Euler* e);
void quaternion_fromEuler(const Euler e, quaternion* q);
float quaternion_getEuler(const quaternion q, int index);
void quaternion_conjugate(const quaternion* q, quaternion* res);

__STATIC_INLINE void quaternion_load_init_attitude(quaternion* q)
{
    q->w = 1;
    q->x = q->y = q->z = 0;
}

#ifdef __cplusplus
}
#endif

#endif
