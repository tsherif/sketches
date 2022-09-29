// Assumes HandmadeMath has been included

typedef struct {
    hmm_vec3 position;
    hmm_vec3 target;
    hmm_vec3 up;
    hmm_mat4 matrix;
} Camera;

void camera_orbit(Camera* camera, float dx, float dy) {
    camera->position = HMM_SubtractVec3(camera->position, camera->target);
    hmm_vec3 axis = HMM_Cross(camera->up, camera->position);
    axis = HMM_NormalizeVec3(axis);
    camera->up = HMM_Cross(camera->position, axis);
    camera->up = HMM_NormalizeVec3(camera->up);

    hmm_mat4 xRotation = HMM_Rotate(dx, camera->up);
    hmm_mat4 yRotation = HMM_Rotate(dy, axis);
    hmm_mat4 rotation = HMM_MultiplyMat4(xRotation, yRotation);

    hmm_vec4 hPosition = HMM_Vec4v(camera->position, 1.0f);
    hPosition = HMM_MultiplyMat4ByVec4(rotation, hPosition);
    camera->position = HMM_AddVec3(hPosition.XYZ, camera->target);
}

void camera_pan(Camera* camera, float dx, float dy) {
    hmm_vec3 forward = HMM_SubtractVec3(camera->target, camera->position);
    hmm_vec3 right = HMM_Cross(forward, camera->up);
    right = HMM_NormalizeVec3(right);

    hmm_vec3 delta = HMM_AddVec3(
        HMM_MultiplyVec3f(right, dx),
        HMM_MultiplyVec3f(camera->up, dy)
    );

    camera->position = HMM_AddVec3(camera->position, delta);
    camera->target = HMM_AddVec3(camera->target, delta);
}

void camera_zoom(Camera* camera, float zoom) {
    camera->position = 
        HMM_AddVec3(
            HMM_MultiplyVec3f(
                HMM_NormalizeVec3(
                    HMM_SubtractVec3(camera->position, camera->target)
                ), 
                zoom
            ), 
            camera->target
        );
}

void camera_buildMatrix(Camera* camera) {
    camera->matrix = HMM_LookAt(camera->position, camera->target, camera->up);
}