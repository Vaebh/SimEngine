#ifndef EVENT_TYPES_SIMENGINE
#define EVENT_TYPES_SIMENGINE

// TODO - add the numpad keys

enum EventType
{
	COLLISION,
	DEATH,

	INPUT_1_PRESS,
	INPUT_1_RELEASE,
	INPUT_2_PRESS,
	INPUT_2_RELEASE,
	INPUT_3_PRESS,
	INPUT_3_RELEASE,
	INPUT_4_PRESS,
	INPUT_4_RELEASE,
	INPUT_5_PRESS,
	INPUT_5_RELEASE,
	INPUT_6_PRESS,
	INPUT_6_RELEASE,
	INPUT_7_PRESS,
	INPUT_7_RELEASE,
	INPUT_8_PRESS,
	INPUT_8_RELEASE,
	INPUT_9_PRESS,
	INPUT_9_RELEASE,
	INPUT_0_PRESS,
	INPUT_0_RELEASE,

	INPUT_MINUS_PRESS,
	INPUT_MINUS_RELEASE,
	INPUT_EQUAL_PRESS,
	INPUT_EQUAL_RELEASE,
	INPUT_BACKSPACE_PRESS,
	INPUT_BACKSPACE_RELEASE,

	INPUT_Q_PRESS,
	INPUT_Q_RELEASE,
	INPUT_W_PRESS,
	INPUT_W_RELEASE,
	INPUT_E_PRESS,
	INPUT_E_RELEASE,
	INPUT_R_PRESS,
	INPUT_R_RELEASE,

	INPUT_T_PRESS,
	INPUT_T_RELEASE,
	INPUT_Y_PRESS,
	INPUT_Y_RELEASE,
	INPUT_U_PRESS,
	INPUT_U_RELEASE,
	INPUT_I_PRESS,
	INPUT_I_RELEASE,

	INPUT_O_PRESS,
	INPUT_O_RELEASE,
	INPUT_P_PRESS,
	INPUT_P_RELEASE,
	INPUT_LEFT_BRACKET_PRESS,
	INPUT_LEFT_BRACKET_RELEASE,
	INPUT_RIGHT_BRACKET_PRESS,
	INPUT_RIGHT_BRACKET_RELEASE,
	INPUT_ENTER_PRESS,
	INPUT_ENTER_RELEASE,
	
	INPUT_A_PRESS,
	INPUT_A_RELEASE,
	INPUT_S_PRESS,
	INPUT_S_RELEASE,
	INPUT_D_PRESS,
	INPUT_D_RELEASE,
	INPUT_F_PRESS,
	INPUT_F_RELEASE,

	INPUT_G_PRESS,
	INPUT_G_RELEASE,
	INPUT_H_PRESS,
	INPUT_H_RELEASE,
	INPUT_J_PRESS,
	INPUT_J_RELEASE,
	INPUT_K_PRESS,
	INPUT_K_RELEASE,

	INPUT_L_PRESS,
	INPUT_L_RELEASE,
	INPUT_SEMICOLON_PRESS,
	INPUT_SEMICOLON_RELEASE,
	INPUT_APOSTROPHE_PRESS,
	INPUT_APOSTROPHE_RELEASE,
	
	INPUT_LEFT_SHIFT_PRESS,
	INPUT_LEFT_SHIFT_RELEASE,
	INPUT_BACKSLASH_PRESS,
	INPUT_BACKSLASH_RELEASE,
	INPUT_Z_PRESS,
	INPUT_Z_RELEASE,
	INPUT_X_PRESS,
	INPUT_X_RELEASE,
	INPUT_C_PRESS,
	INPUT_C_RELEASE,

	INPUT_V_PRESS,
	INPUT_V_RELEASE,
	INPUT_B_PRESS,
	INPUT_B_RELEASE,
	INPUT_N_PRESS,
	INPUT_N_RELEASE,
	INPUT_M_PRESS,
	INPUT_M_RELEASE,

	INPUT_COMMA_PRESS,
	INPUT_COMMA_RELEASE,
	INPUT_PERIOD_PRESS,
	INPUT_PERIOD_RELEASE,
	INPUT_SLASH_PRESS,
	INPUT_SLASH_RELEASE,
	INPUT_RIGHT_SHIFT_PRESS,
	INPUT_RIGHT_SHIFT_RELEASE,

	INPUT_LEFT_CONTROL_PRESS,
	INPUT_LEFT_CONTROL_RELEASE,
	INPUT_LEFT_ALT_PRESS,
	INPUT_LEFT_ALT_RELEASE,
	INPUT_SPACE_PRESS,
	INPUT_SPACE_RELEASE,
	INPUT_RIGHT_ALT_PRESS,
	INPUT_RIGHT_ALT_RELEASE,
	INPUT_RIGHT_CONTROL_PRESS,
	INPUT_RIGHT_CONTROL_RELEASE,

	INPUT_LEFT_PRESS,
	INPUT_LEFT_RELEASE,
	INPUT_DOWN_PRESS,
	INPUT_DOWN_RELEASE,
	INPUT_RIGHT_PRESS,
	INPUT_RIGHT_RELEASE,
	INPUT_UP_PRESS,
	INPUT_UP_RELEASE,

	INPUT_LEFT_CLICK_PRESS,
	INPUT_LEFT_CLICK_RELEASE,
	INPUT_RIGHT_CLICK_PRESS,
	INPUT_RIGHT_CLICK_RELEASE,

	NUM_EVENTS
};

#endif