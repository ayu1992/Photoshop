PhotoShop Additions:

GLUI library
==============================================================
    - Bug fixes in File Browser functionality
    - Bug fix in Double Click functionality

BaseGfxApp.h/.cpp
==============================================================
    - void setWindowDimensions(int width, int height);


PhotoShop.h/.cpp
==============================================================
    - Bug fix in gluiControl(). Forces redraw canvas at end of function.

// GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_COLOR_R,
        UI_COLOR_G,
        UI_COLOR_B,
        UI_PRESET_RED,
        UI_PRESET_ORANGE,
        UI_PRESET_YELLOW,
        UI_PRESET_GREEN,
        UI_PRESET_BLUE,
        UI_PRESET_PURPLE,
        UI_PRESET_WHITE,
        UI_PRESET_BLACK,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_LOAD_STAMP_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_BLUR,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_DITHER,
        UI_APPLY_SATURATE,
        UI_APPLY_CHANNEL,
        UI_APPLY_QUANTIZE,
        UI_APPLY_MOTION_BLUR,
        UI_APPLY_SPECIAL_FILTER,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };

    void setImageFile(const std::string & filepath);
    bool isValidImageFileName(const std::string & name);
    bool isValidImageFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    void loadStampEnabled(bool enabled);
    void updateColors();
    
    void loadImageToCanvas();
    void loadImageToStamp();
    void saveCanvasToFile();
    
    void applyFilterBlur();
    void applyFilterSharpen();
    void applyFilterMotionBlur();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterChannel();
    void applyFilterSaturate();
    void applyFilterQuantize();
    void applyFilterSpecial();
    
    void undoOperation();
    void redoOperation();
    
    enum UIMotionBlurDirections {
        DIR_N_S,
        DIR_E_W,
        DIR_NE_SW,
        DIR_NW_SE
    };
    
    struct {
        float channel_colorRed;
        float channel_colorGreen;
        float channel_colorBlue;
        float saturation_amount;
        float threshold_amount;
        float blur_amount;
        float sharpen_amount;
        float motionBlur_amount;
        int motionBlur_direction;
        int quantize_bins;
    } m_filterParameters;
    
    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *loadStampButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;
        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;
        
        GLUI_Spinner *spinnerRed;
        GLUI_Spinner *spinnerGreen;
        GLUI_Spinner *spinnerBlue;
    } m_gluiControlHooks;
