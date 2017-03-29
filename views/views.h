void drawLoginSuccessScreen(void);
void drawLogoutSuccessScreen(void);
void drawMainScreen(int userId);
void drawLoginScreen(void);
void displayPopup(char* msg, int size, int backgroundColour);
int loginVerification(void);
void drawCurrentUser(int userIndex);
void mainScreenFunctionality(void);
int passwordVerification(int userIndex, char* password);
void drawUserPasswordPrompt(int userIndex);
void drawGPSData(char* longitude, char* latitude);
void drawIntroScreen(void);
void drawPixelBlock(int x, int y, int Colour);
void drawLogo(int x, int y);
void drawSendingGPS(void);
void drawLoadingBar(int p);

int checkLoginId(char* userId);
void clearId(void);
