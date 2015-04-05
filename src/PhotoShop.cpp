#include "PhotoShop.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "ToolFactory.h" 
#include "Tool.h"
#include "PixelBufferManager.h"
#include "IOHandler.h"
#include "Util.h"
#include "Threshold.h"
#include "Saturate.h"
#include "Channels.h"
#include "Quantize.h"
#include <cmath>

using std::cout;
using std::endl;

PhotoShop::PhotoShop(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50),m_displayBuffer(NULL)
{
    // Set the name of the window
    setCaption("PhotoShop");
    
    // Initialize Interface
    
    initializeBuffers(backgroundColor, width, height);
    initGlui();
    initGraphics();
}

void PhotoShop::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

PhotoShop::~PhotoShop()
{
    if (m_displayBuffer) {
        delete m_displayBuffer;
    }
}


void PhotoShop::mouseDragged(int x, int y)
{

    Tool* currentTool = m_toolFactory.getTool(getCurrentToolType(), m_curSize);
    if(currentTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }

    int max_steps = 25;
    int height = m_displayBuffer->getHeight(); 

    int delta_x = x-m_mouseLastX;
    int delta_y = y-m_mouseLastY;

    float pixelsBetween = fmax(abs(delta_x), abs(delta_y));
    int step_count = pixelsBetween;
    int step_size = 1;
    
    if (pixelsBetween > max_steps){
        step_size = pixelsBetween/max_steps;
        step_count = max_steps;
    }
    
    for (int i = 0; i < pixelsBetween; i+=step_size) 
    {
        int x = m_mouseLastX+(i*delta_x/pixelsBetween);
        int y = m_mouseLastY+(i*delta_y/pixelsBetween);
        
        currentTool->setStartPoint(x,height-y);
        currentTool->applyToolOnCanvas(m_displayBuffer); 
    }

    m_mouseLastX = x;
    m_mouseLastY = y;

    /*TODO for mask based and interactive tools */
    
    
}

void PhotoShop::mouseMoved(int x, int y)
{
    
}

void PhotoShop::leftMouseDown(int x, int y)
{
    /*TODO for mask based and interactive tools */
    // get requested Tool instance
    Tool* currentTool = m_toolFactory.getTool(getCurrentToolType(), m_curSize);
    int height = m_displayBuffer->getHeight();
    if(currentTool == NULL){
        std::cout << "current tool is null"<< endl;
        return;
    } 
    // set up tool color and position
    currentTool->setStartPoint(x,height - y);
    currentTool->setCurrentColor(ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue));
    currentTool->applyToolOnCanvas(m_displayBuffer);

    m_mouseLastX = x;
    m_mouseLastY = y;
}

void PhotoShop::leftMouseUp(int x, int y)
{
    takeSnapshot(m_displayBuffer);
}

void PhotoShop::initializeBuffers(ColorData backgroundColor, int width, int height) {
    takeSnapshot(new PixelBuffer(width, height, backgroundColor));
    loadSnapshot(m_pbManager.getLatestSnapshot());
}

void PhotoShop::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;
    m_curSize = 1;

    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
        new GLUI_RadioButton(radio, "Eraser");
        new GLUI_RadioButton(radio, "Spray Can");
        new GLUI_RadioButton(radio, "Caligraphy Pen");
        new GLUI_RadioButton(radio, "Highlighter");
        new GLUI_RadioButton(radio, "Stamp");
        new GLUI_RadioButton(radio, "Blur");

        //Tool size panel
        GLUI_Panel *sizePanel = new GLUI_Panel(m_glui, "Size");
        GLUI_RadioGroup *maskRadio = new GLUI_RadioGroup(sizePanel, &m_curSize, UI_TOOLTYPE, s_gluicallback);    
        new GLUI_RadioButton(maskRadio, "Small");//0
        new GLUI_RadioButton(maskRadio, "Medium");//1
        new GLUI_RadioButton(maskRadio, "Large");//2
    }
    
    GLUI_Panel *colorPanel = new GLUI_Panel(m_glui, "Tool Color");
    {
        m_curColorRed = 0;
        m_gluiControlHooks.spinnerRed  = new GLUI_Spinner(colorPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
        m_gluiControlHooks.spinnerRed->set_float_limits(0, 1.0);
        
        m_curColorGreen = 0;
        m_gluiControlHooks.spinnerGreen  = new GLUI_Spinner(colorPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
        m_gluiControlHooks.spinnerGreen->set_float_limits(0, 1.0);
        
        m_curColorBlue = 0;
        m_gluiControlHooks.spinnerBlue  = new GLUI_Spinner(colorPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
        m_gluiControlHooks.spinnerBlue->set_float_limits(0, 1.0);
        
        new GLUI_Button(colorPanel, "Red", UI_PRESET_RED, s_gluicallback);
        new GLUI_Button(colorPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
        new GLUI_Button(colorPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
        new GLUI_Button(colorPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
        new GLUI_Button(colorPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
        new GLUI_Button(colorPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
        new GLUI_Button(colorPanel, "White", UI_PRESET_WHITE, s_gluicallback);
        new GLUI_Button(colorPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
    }
    
    // UNDO,REDO,QUIT
    {
        m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
        undoEnabled(false);
        m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
        redoEnabled(false);
        
        new GLUI_Separator(m_glui);
        new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
    }
    
    new GLUI_Column(m_glui, true);
    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *blurPanel = new GLUI_Panel(filterPanel, "Blur");
        {
            GLUI_Spinner * filterBlurAmount = new GLUI_Spinner(blurPanel, "Amount:", &m_filterParameters.blur_amount);
            filterBlurAmount->set_int_limits(0, 20);
            
            filterBlurAmount->set_int_val(5);
            
            new GLUI_Button(blurPanel, "Apply", UI_APPLY_BLUR, s_gluicallback);
        }
        
        GLUI_Panel *motionBlurPanel = new GLUI_Panel(filterPanel, "MotionBlur");
        {
            GLUI_Spinner * filterMotionBlurAmount = new GLUI_Spinner(motionBlurPanel, "Amount:", &m_filterParameters.motionBlur_amount);
            filterMotionBlurAmount->set_int_limits(0, 100);
            
            filterMotionBlurAmount->set_int_val(5);
            
            m_filterParameters.motionBlur_direction = 0;
            GLUI_RadioGroup *dirBlur = new GLUI_RadioGroup(motionBlurPanel, &m_filterParameters.motionBlur_direction);
            new GLUI_RadioButton(dirBlur, "North/South");
            new GLUI_RadioButton(dirBlur, "East/West");
            new GLUI_RadioButton(dirBlur, "NorthEast/SouthWest");
            new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");
            
            new GLUI_Button(motionBlurPanel, "Apply", UI_APPLY_MOTION_BLUR, s_gluicallback);
        }
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(0, 100);
            
            filterSharpAmount->set_int_val(5);
            
            new GLUI_Button(sharpenPanel, "Apply", UI_APPLY_SHARP, s_gluicallback);
        }
        GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");
        
        {
            new GLUI_Button(edgeDetPanel, "Apply", UI_APPLY_EDGE, s_gluicallback);
        }
        GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
        {
            GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel, "Level:", &m_filterParameters.threshold_amount);
            filterThresholdAmount->set_float_limits(0, 1);
            filterThresholdAmount->set_float_val(0.5);
            
            new GLUI_Button(thresPanel, "Apply", UI_APPLY_THRESHOLD, s_gluicallback);
        }
        
        GLUI_Panel *saturPanel = new GLUI_Panel(filterPanel, "Saturation");
        {
            GLUI_Spinner * filterSaturationAmount = new GLUI_Spinner(saturPanel, "Amount:", &m_filterParameters.saturation_amount);
            filterSaturationAmount->set_float_limits(-10, 10);
            filterSaturationAmount->set_float_val(1);
            
            new GLUI_Button(saturPanel, "Apply", UI_APPLY_SATURATE, s_gluicallback);
        }
        
        GLUI_Panel *channelPanel = new GLUI_Panel(filterPanel, "Channels");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(channelPanel, "Red:", &m_filterParameters.channel_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(channelPanel, "Green:", &m_filterParameters.channel_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(channelPanel, "Blue:", &m_filterParameters.channel_colorBlue);
            
            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);
            
            new GLUI_Button(channelPanel, "Apply", UI_APPLY_CHANNEL, s_gluicallback);
        }
        
        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);
            
            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }
        
        GLUI_Panel *specialFilterPanel = new GLUI_Panel(filterPanel, "Special Filter"); // YOUR SPECIAL FILTER PANEL
        {
            new GLUI_Button(specialFilterPanel, "Apply", UI_APPLY_SPECIAL_FILTER, s_gluicallback);
        }
    }
    
    new GLUI_Column(m_glui, true);

    GLUI_Panel *imagePanel = new GLUI_Panel(m_glui, "Image I/O");
    {
        m_gluiControlHooks.fileBrowser = new GLUI_FileBrowser(imagePanel, "Choose Image", false, UI_FILE_BROWSER, s_gluicallback);
        
        m_gluiControlHooks.fileBrowser->set_h(400);
        
        m_gluiControlHooks.fileNameBox = new     GLUI_EditText( imagePanel , "Image:", m_fileName, UI_FILE_NAME, s_gluicallback );
        m_gluiControlHooks.fileNameBox->set_w(200);

        new GLUI_Separator(imagePanel);
        
        m_gluiControlHooks.currentFileLabel = new GLUI_StaticText(imagePanel, "Will load image: none");
        m_gluiControlHooks.loadCanvasButton = new GLUI_Button(imagePanel, "Load Canvas", UI_LOAD_CANVAS_BUTTON, s_gluicallback);
        m_gluiControlHooks.loadStampButton = new GLUI_Button(imagePanel, "Load Stamp", UI_LOAD_STAMP_BUTTON, s_gluicallback);
        
        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");
        
        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);
        
        loadCanvasEnabled(true);
        loadStampEnabled(true);
        saveCanvasEnabled(true);
    }
    return;
}

void PhotoShop::gluiControl(int controlID)
{
    
    switch (controlID) {
        case UI_PRESET_RED:
            m_curColorRed = 1;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_ORANGE:
            m_curColorRed = 1;
            m_curColorGreen = 0.5;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_YELLOW:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_GREEN:
            m_curColorRed = 0;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_BLUE:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_PURPLE:
            m_curColorRed = 0.5;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_WHITE:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_BLACK:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_APPLY_BLUR:
            applyFilterBlur();
            break;
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_MOTION_BLUR:
            applyFilterMotionBlur();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_DITHER:
            applyFilterThreshold();
            break;
        case UI_APPLY_SATURATE:
            applyFilterSaturate();
            break;
        case UI_APPLY_CHANNEL:
            applyFilterChannel();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_APPLY_SPECIAL_FILTER:
            applyFilterSpecial();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_LOAD_STAMP_BUTTON:
            loadImageToStamp();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_FILE_NAME:
            setImageFile(m_fileName);
            break;
        case UI_UNDO:
            undoOperation();
            break;
        case UI_REDO:
            redoOperation();
            break;
        default:
            break;
    }
    
    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();
}

// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how PhotoShop should respond to the
// button presses.

// this function is only called by undo,redo,loadImage
void PhotoShop::loadSnapshot(PixelBuffer* newCanvas){
    if(m_displayBuffer) delete m_displayBuffer;       
    m_displayBuffer = newCanvas;
    setWindowDimensions(m_displayBuffer->getWidth(),m_displayBuffer->getHeight()); 
    //cout<<"loading snapshot"<<endl;
    //undoEnabled(m_pbManager.canUndo());
    //redoEnabled(m_pbManager.canRedo());
}

void PhotoShop::takeSnapshot(PixelBuffer* unsaved){
    m_pbManager.takeSnapshot(unsaved);
    //cout<<"taking snapshot"<<endl;
    //undoEnabled(m_pbManager.canUndo());
    //redoEnabled(m_pbManager.canRedo());
}
void PhotoShop::loadImageToCanvas()
{
    PixelBuffer *local = m_ioHandler.readImage(m_fileName);
    /*TODO: handle read fail*/
    takeSnapshot(local);      // manager now owns a copy
    // display the copied version
    delete local;
    loadSnapshot(m_pbManager.getLatestSnapshot());

}

void PhotoShop::loadImageToStamp()
{   PixelBuffer *stamp = m_ioHandler.readImage(m_fileName);
    
}

void PhotoShop::saveCanvasToFile()
{   
    // pass a copy of m_displayBuffer instead
    m_ioHandler.writeImage((std::string("new_") + m_fileName), m_displayBuffer);
    cout<<" file write complete"<<endl;
}

void PhotoShop::applyFilterThreshold()
{
    Tool* thresholdTool = m_toolFactory.getTool(ToolFactory::THRESHOLD,0);
    if(thresholdTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    static_cast<Threshold *>(thresholdTool)->applyThreshold(m_displayBuffer, m_filterParameters.threshold_amount);
    takeSnapshot(m_displayBuffer);
}

void PhotoShop::applyFilterChannel()
{
    Tool* channelsTool = m_toolFactory.getTool(ToolFactory::CHANNELS,0);
    if(channelsTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    static_cast<Channels *>(channelsTool)->applyChannels(m_displayBuffer, m_filterParameters.channel_colorRed, m_filterParameters.channel_colorGreen, m_filterParameters.channel_colorBlue);
    takeSnapshot(m_displayBuffer);
}

void PhotoShop::applyFilterSaturate()
{
    Tool* saturateTool = m_toolFactory.getTool(ToolFactory::SATURATE,0);
    if(saturateTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    static_cast<Saturate *>(saturateTool)->applySaturate(m_displayBuffer,  m_filterParameters.saturation_amount);
    takeSnapshot(m_displayBuffer);
}

void PhotoShop::applyFilterBlur()
{
    Tool* blurTool = m_toolFactory.getTool(ToolFactory::BLUR,m_filterParameters.blur_amount);
    if(blurTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    // merge?
    blurTool->applyToolOnCanvas(m_displayBuffer);
    takeSnapshot(m_displayBuffer);

}

void PhotoShop::applyFilterSharpen()
{
    Tool* sharpenTool = m_toolFactory.getTool(ToolFactory::SHARPEN,m_filterParameters.blur_amount);
    if(sharpenTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    // merge?
    sharpenTool->applyToolOnCanvas(m_displayBuffer);
    takeSnapshot(m_displayBuffer);
}

void PhotoShop::applyFilterMotionBlur()
{
    Tool* motionBlurTool = m_toolFactory.getMotionBlurTool(m_filterParameters.motionBlur_amount,m_filterParameters.motionBlur_direction);
    if(motionBlurTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    // merge?
    motionBlurTool->applyToolOnCanvas(m_displayBuffer);
    takeSnapshot(m_displayBuffer);
}

void PhotoShop::applyFilterEdgeDetect() {
    Tool* edgeDetectTool = m_toolFactory.getTool(ToolFactory::EDGE_DETECTION,0);
    if(edgeDetectTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    // merge?
    edgeDetectTool->applyToolOnCanvas(m_displayBuffer);
    takeSnapshot(m_displayBuffer);
}

void PhotoShop::applyFilterQuantize() {

    Tool* quantizeTool = m_toolFactory.getTool(ToolFactory::QUANTIZE,0);
    if(quantizeTool == NULL){
        std::cout<<"current tool is NULL"<<std::endl;
        return;
    }
    static_cast<Quantize *>(quantizeTool)->applyQuantize(m_displayBuffer, m_filterParameters.quantize_bins);
    takeSnapshot(m_displayBuffer);

}

void PhotoShop::applyFilterSpecial() {
    cout << "Apply has been clicked for Special" << endl;
}

void PhotoShop::undoOperation()
{
    cout << "Undoing..." << endl;
    m_pbManager.undo();
    loadSnapshot(m_pbManager.getLatestSnapshot());
}

void PhotoShop::redoOperation()
{
    cout << "Redoing..." << endl;
    m_pbManager.redo();
    loadSnapshot(m_pbManager.getLatestSnapshot());
}
// ** END OF CALLBACKS **
// **********************


// **********************
// Provided code for managing the
// GLUI interface.

void PhotoShop::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void PhotoShop::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void PhotoShop::undoEnabled(bool enabled)
{
    cout<<"calling undoEnabled"<<endl;
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
    cout<<"finish undoEnabled"<<endl;
}

void PhotoShop::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void PhotoShop::loadStampEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadStampButton, enabled);
}

void PhotoShop::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void PhotoShop::updateColors() {
    m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
    m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
    m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
}


bool PhotoShop::isValidImageFileName(const std::string & name) {
    
    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool PhotoShop::isValidImageFile(const std::string & name) {
    
    FILE *f;
    bool isValid = false;
    if (isValidImageFileName(name)) {
        if ((f = fopen( name.c_str(), "r"))) {
            isValid = true;
            fclose(f);
        }
    }
    return isValid;
}

void PhotoShop::setImageFile(const std::string & fileName)
{
    // If a directory was selected
    // instead of a file, use the
    // latest file typed or selected.
    std::string imageFile = fileName;
    if (!isValidImageFileName(imageFile)) {
        imageFile = m_fileName;
    }
    
    
    // TOGGLE SAVE FEATURE
    // If no file is selected or typed,
    // don't allow file to be saved. If
    // there is a file name, then allow
    // file to be saved to that name.
    
    if (!isValidImageFileName(imageFile)) {
        m_gluiControlHooks.saveFileLabel->set_text("Will save image: none");
        saveCanvasEnabled(false);
    } else {
        m_gluiControlHooks.saveFileLabel->set_text((std::string("Will save image: ") + imageFile).c_str());
        saveCanvasEnabled(true);
    }
    
    // TOGGLE LOAD FEATURE
    
    // If the file specified cannot be opened,
    // then disable stamp and canvas loading.
    if (isValidImageFile(imageFile)) {
        loadStampEnabled(true);
        loadCanvasEnabled(true);
        
        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);
    } else {
        loadStampEnabled(false);
        loadCanvasEnabled(false);
        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

ToolFactory::ToolType PhotoShop::getCurrentToolType(){
    return static_cast<ToolFactory::ToolType>(m_curTool);
}