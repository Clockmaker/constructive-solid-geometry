/* ui.h */
#ifndef UI_H
#define UI_H

struct uiState_s { 
	float width, height, aspect;

} UI;

struct camera_s {
	vec3 pos;//x,y,z
	vec3 rot;//roll, pitch, yaw;
	vec3 pan;
	mat4 projection;
	mat4 view;
	mat4 matrix;

	float zoom;
	struct {
		vec3 rot;
	}last;
};
extern struct camera_s Camera;

void UI_init(void);
void UI_frame(void);
void UI_refresh(int width, int height);

#endif