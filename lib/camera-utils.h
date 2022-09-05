// Assumes HandmadeMath has been included

void orbitCamera(hmm_vec3* pEye, hmm_vec3* pLook, hmm_vec3* pUp, float x, float y) {
    hmm_vec3 eye = *pEye;
    hmm_vec3 look = *pLook;
    hmm_vec3 up = *pUp;

    eye = HMM_SubtractVec3(eye, look);
    hmm_vec3 axis = HMM_Cross(up, eye);
    axis = HMM_NormalizeVec3(axis);
    up = HMM_Cross(eye, axis);
    up = HMM_NormalizeVec3(up);

    // HMM_Rotate
    hmm_mat4 xRotation = HMM_Rotate(x, up);
    hmm_mat4 yRotation = HMM_Rotate(y, axis);
    hmm_mat4 rotation = HMM_MultiplyMat4(xRotation, yRotation);

    hmm_vec4 hEye = HMM_Vec4v(eye, 1.0f);
    hEye = HMM_MultiplyMat4ByVec4(rotation, hEye);
    eye = HMM_AddVec3(hEye.XYZ, look);

    *pEye = eye;
    *pLook = look;
    *pUp = up;
}

void zoomCamera(hmm_vec3* pEye, hmm_vec3* pLook, float zoom) {
    hmm_vec3 eye = *pEye;
    hmm_vec3 look = *pLook;

    *pEye = 
        HMM_AddVec3(
            HMM_MultiplyVec3f(
                HMM_NormalizeVec3(
                    HMM_SubtractVec3(eye, look)
                ), 
                zoom
            ), 
            look
        );
}