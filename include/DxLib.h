/*
  DxPortLib - A portability library for DxLib-based software.
  Copyright (C) 2013 Patrick McCarthy <mauve@sandwich.net>
  
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
    
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required. 
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
 */

#ifndef DXLIB_H_HEADER
#define DXLIB_H_HEADER

// This is the C++ interface. It's just a wrapper to the C core.

// EXT_ is used for DxPortLib extensions.

#include "DxBuildConfig.h"

#include "DxDefines.h"

// For size_t.
#include <stdlib.h>

namespace DxLib {

// -------------------------------------------------------------- DxLib.cpp

// - Open the DxLib wrapper library.
// After setting initialization parameters, call this function.
extern DXCALL int DxLib_Init(void);

// - Closes the DxLib wrapper library.
// Call when your program is finished.
extern DXCALL int DxLib_End(void);

// - Reset initalization parameters to default.
// Can only be called before DxLib_Init.
extern DXCALL int DxLib_GlobalStructInitialize(void);

// - Returns TRUE if DxLib_Init has been called, FALSE otherwise.
extern DXCALL int DxLib_IsInit(void);

// - Handle window messages and updates as neecessary.
// Call this as part of your main loop.
// Returns -1 when the program is finished.
extern DXCALL int ProcessMessage(void);

// - Waits the given number of milliseconds.
extern DXCALL int WaitTimer(int msTime);

// - Waits for a key to be pressed.
extern DXCALL int WaitKey();

// - Gets the time since program start, in milliseconds.
extern DXCALL int GetNowCount();

// - Gets a random value from [0...RandMax]
extern DXCALL int GetRand(int maxValue);

// - Seeds the random number generator with the given seed value.
// Internally, the Mersenne Twister is used.
extern DXCALL int SRand(int randomSeed);

// - Sets if logging is enabled or not.
// NOTICE: Because Log has not been written, this does nothing.
extern DXCALL int SetOutApplicationLogValidFlag(int logFlag);

// - Sets the contents of flag to -1 when the handle is deleted.
extern DXCALL int SetDeleteHandleFlag(int handleID, int *flag);

// - Sets the default character set used.
// DxPortLib uses UTF8 by default.
// It is highly recommended to build your application to use UTF8.
extern DXCALL int SetUseCharSet(int charset);

// ------------------------------------------------------------- DxFile.cpp
// - DxPortLib extension: Sets the charset to use with FileRead strings.
// Defaults to the currently active character set.
extern DXCALL int EXT_FileRead_SetCharSet(int charset);

// - Opens a file stream handle to the given file.
// Returns -1 on failure, otherwise returns the stream handle.
extern DXCALL int FileRead_open(const DXCHAR *filename);

// - Returns the size of the file.
extern DXCALL long long FileRead_size(int fileHandle);

// - Closes the file stream handle.
extern DXCALL int FileRead_close(int fileHandle);

// - Returns the current position within the file stream.
extern DXCALL long long FileRead_tell(int fileHandle);

// - Seeks to a given position within the file.
// Origin may have the following values:
// SEEK_SET: Seeks to the given position.
// SEEK_CUR: Seek to an offset from the current position.
// SEEK_END: Seek to an offset from the end of the file.
// Returns the new position within the file.
extern DXCALL int FileRead_seek(int fileHandle,
                                long long position, int origin);

// - Reads size bytes from the file, storing in the data pointer.
// Returns the number of bytes read.
extern DXCALL int FileRead_read(void *data, int size, int fileHandle);

// - Returns TRUE if the current position is at the end of the file.
extern DXCALL int FileRead_eof(int fileHandle);

// - Reads a single line of text from the file, returns length.
extern DXCALL int FileRead_gets(DXCHAR *buffer,
                                int bufferSize, int fileHandle);

// - Reads a single character.
extern DXCALL DXCHAR FileRead_getc(int fileHandle);

// - Performas a scanf() on the next line of text in the file.
extern DXCALL int FileRead_scanf(int fileHandle,
                                 const DXCHAR *format, ...);

// ---------------------------------------------------------- DxArchive.cpp
// - If true, will attempt to load data from dirname.dxa.
// e.g. "directory/blah.txt" looks for "blah.txt" in "directory.dxa"
extern DXCALL int SetUseDXArchiveFlag(bool flag);

// - Sets the encryption key to be used for DXA files.
extern DXCALL int SetDXArchiveKeyString(const DXCHAR *keyString);

// - Sets the filename extension to be used for DXA files.
// Default is "dxa".
// NOTICE: Non-Windows platforms are case sensitive!
extern DXCALL int SetDXArchiveExtension(const DXCHAR *extension);

// - If FALSE, tries to load from dxa files then normal files.
//   If TRUE, tries to load from normal files then dxa files.
extern DXCALL int SetDXArchivePriority(int flag);

// - Preloads the dxa archive to memory.
// NOTICE: async is not supported and will be ignored.
extern DXCALL int DXArchivePreLoad(const DXCHAR *dxaFilename,
                                   int async = DXFALSE);

// - Returns TRUE if preloading has been completed.
// NOTICE: As async is not supported, this will always be TRUE.
extern DXCALL int DXArchiveCheckIdle(const DXCHAR *dxaFilename);

// - Releases the archive data from memory.
extern DXCALL int DXArchiveRelease(const DXCHAR *dxaFilename);

// - Returns TRUE if filename is contained within the
//   archive pointed to by dxaFilename.
extern DXCALL int DXArchiveCheckFile(const DXCHAR *dxaFilename,
                                     const DXCHAR *filename);

// ------------------------------------------------------------ DxInput.cpp
#ifndef DX_NON_INPUT

// - Checks to see if the given EY_INPUT code has been pressed.
extern DXCALL int CheckHitKey(int keyCode);

// - Checks to see if any key is hit.
//   Depending on CHECKINPUT flags, will also check for
//   joypad and mouse input.
extern DXCALL int CheckHitKeyAll(int checkType = DX_CHECKINPUT_ALL);

// - Gets the table of all pressed keys.
extern DXCALL int GetHitKeyStateAll(char *table);

// - Gets number of connected joypads.
extern DXCALL int GetJoypadNum();

// - Gets the bitmasked state of the given joypad index.
extern DXCALL int GetJoypadInputState(int controllerIndex);

// - Gets the DirectInput POV of a given joypad index.
// Returns -1 if POV is in neutral, otherwise its position.
extern DXCALL int GetJoypadPOVState(int controllerIndex, int povNumber);

// - Gets the DirectInput state of a given joypad index.
// Returns -1 if invalid.
extern DXCALL int GetJoypadDirectInputState(int controllerIndex,
                                            DINPUT_JOYSTATE *state);

// - Gets the XInput state of a given joypad index.
// Returns -1 if invalid.
extern DXCALL int GetJoypadXInputState(int controllerIndex,
                                       XINPUT_STATE *state);

// - Sets the associated keybinds for a given joystick input.
extern DXCALL int SetJoypadInputToKeyInput(int controllerIndex, int input,
                                    int key1, int key2 = 0,
                                    int key3 = 0, int key4 = 0);

// - Gets the mouse position.
extern DXCALL int GetMousePoint(int *xPosition, int *yPosition);
// - Sets the mouse positon.
extern DXCALL int SetMousePoint(int xPosition, int yPosition);
// - Gets the bitmasked state of mouse buttons.
extern DXCALL int GetMouseInput();

// - Gets the Vertical or Horizontal mouse wheel states.
// If clearFlag, resets internal value to zero.
extern DXCALL int GetMouseWheelRotVol(int clearFlag);
extern DXCALL int GetMouseHWheelRotVol(int clearFlag);
extern DXCALL float GetMouseWheelRotVolF(int clearFlag);
extern DXCALL float GetMouseHWheelRotVolF(int clearFlag);

#endif /* #ifndef DX_NON_INPUT */

// ----------------------------------------------------------- DxWindow.cpp
// - Sets the size of the target draw buffer.
// NOTICE: For DxPortLib, this may not be the actual window size!
// NOTICE: bitDepth and FPS are ignored in DxPortLib! Always 32, 60.
extern DXCALL int SetGraphMode(int width, int height,
                               int bitDepth, int FPS = 60);

// - Sets if the window can be resized or not.
// NOTICE: Can only be set before DxLib_Init is called!
extern DXCALL int SetWindowSizeChangeEnableFlag(int windowResizeFlag);

// Avoid conflicts with windows headers that will define SetWindowText.
#ifdef SetWindowText
#  undef SetWindowText
#endif

// - Sets the title of the window.
extern DXCALL int SetWindowText(const DXCHAR *windowName);
extern DXCALL int SetMainWindowText(const DXCHAR *windowName);

// - Flips the backbuffer to the front buffer.
// Call when drawing operations for a frame are finished.
extern DXCALL int ScreenFlip();

// - TRUE to use a window, FALSE(default) for fullscreen mode.
extern DXCALL int ChangeWindowMode(int fullscreenFlag);

// - Sets the screen graph that is currently drawn to.
// NOTICE: DxPortLib treats all internally named buffers as identical.
extern DXCALL int SetDrawScreen(int screenName);

// - Gets the screen graph that is currently drawn to.
// Both functions are identical.
// NOTICE: DxPortLib always returns DX_SCREEN_BACK for the main screen.
extern DXCALL int GetDrawScreen();
extern DXCALL int GetActiveGraph();

// - If TRUE, waits for VSync to draw, in order to remove tearing.
// NOTICE: Can only be called before DxLib_Init!
extern DXCALL int SetWaitVSyncFlag(int flag);
extern DXCALL int GetWaitVSyncFlag();

// - DxPortLib Extension: Sets the icon file to use.
// NOTICE: Cannot use resource icons. Supply a .png.
extern DXCALL int EXT_SetIconImageFile(const DXCHAR *filename);

// - If TRUE, runs even if the window is not focused.
// Default is FALSE.
extern DXCALL int SetAlwaysRunFlag(int flag);
extern DXCALL int GetAlwaysRunFlag();

// - If TRUE, displays the mouse cursor, othersise hides.
// Default is TRUE.
extern DXCALL int SetMouseDispFlag(int flag);
extern DXCALL int GetMouseDispFlag(int flag);

// - Creates an error message box.
extern DXCALL int EXT_MessageBoxError(const DXCHAR *title,
                                      const DXCHAR *text);
// - Creates a message box asking a yes/no question.
// Default selected button is button1.
// MessageBoxYesNo returns -1 on error, 0 for button1, 1 for button2.
extern DXCALL int EXT_MessageBoxYesNo(const DXCHAR *title,
                                      const DXCHAR *text,
                                      const DXCHAR *button1,
                                      const DXCHAR *button2);

// --------------------------------------------------------- DxGraphics.cpp
// - Creates a screen graph that can be used with SetDrawScreen.
// Note that you can't use it to draw with while bound.
extern DXCALL int MakeScreen(int width, int height, int hasAlphaChannel);

// - Loads the given image file into the returned handle.
extern DXCALL int LoadGraph(const DXCHAR *name);

// - Loads the given image flipped horizontally into the returned handle.
extern DXCALL int LoadReverseGraph(const DXCHAR *name);

// - Loads an image, and then derives into graphCount graphics handles,
//   placing them into handleBuf.
// e.g.:
//   int handles[16];
//   LoadDivGraph("image.png", 16, 4, 4, 64, 64, handles);
extern DXCALL int LoadDivGraph(
                          const DXCHAR *filename, int graphCount,
                          int xCount, int yCount, int xSize, int ySize,
                          int *handleBuf);
extern DXCALL int LoadDivBmpGraph(
                          const DXCHAR *filename, int graphCount,
                          int xCount, int yCount, int xSize, int ySize,
                          int *handleBuf, int textureFlag, int flipFlag);
extern DXCALL int LoadReverseDivGraph(
                          const DXCHAR *filename, int graphCount,
                          int xCount, int yCount, int xSize, int ySize,
                          int *handleBuf);

// - Deletes a Graph handle.
extern DXCALL int DeleteGraph(int graphID);
// - Deletes all graph handles that were based on the same graph as this.
extern DXCALL int DeleteSharingGraph(int graphID);
// - Deletes ALL Graph handles.
extern DXCALL int InitGraph();

// - Gets the number of currently active graphs.
extern DXCALL int GetGraphNum();

// - Creates a new Graph handle that is a subset of another Graph.
// This does not create a separate image.
// The original graph may be safely deleted.
extern DXCALL int DerivationGraph(int x, int y, int w, int h,
                                  int graphID);

// - Puts the dimensions of the graph into the values pointed to by
//   width and height.
extern DXCALL int GetGraphSize(int graphID, int *width, int *height);

// - Sets the transparent color key to be used when loading images.
// NOTICE: This is not valid after the image has been loaded.
extern DXCALL int SetTransColor(int r, int g, int b);
// - Gets the current transparent color key.
extern DXCALL int GetTransColor(int *r, int *g, int *b);
// - TRUE if the transparent color key is to be used.
// Default is TRUE.
extern DXCALL int SetUseTransColor(int flag);

// NOTICE: For all drawing functions, the following applies:
// - FillFlag, if TRUE, will draw a solid. Otherwise, edges only.
// - blendFlag, if TRUE, draws with blending enabled.
// - turn or turnFlag, if TRUE, will flip the graph horizontally.

// - Draws a pixel at (x,y) with the given color.
extern DXCALL int DrawPixel(int x, int y, DXCOLOR color);

// - Draws a line from (x1,y1) to (x2,y2) with the given color.
extern DXCALL int DrawLine(int x1, int y1, int x2, int y2,
                           DXCOLOR color, int thickness = 1);
extern DXCALL int DrawLineF(float x1, float y1, float x2, float y2,
                            DXCOLOR color, int thickness = 1);

// - Draws a box from (x1,y1) to (x2,y2) with the given color.
//   If FillFlag is set, draws a filled box, otherwise a rectangle.
extern DXCALL int DrawBox(int x1, int y1, int x2, int y2,
                          DXCOLOR color, int FillFlag);
extern DXCALL int DrawBoxF(float x1, float y1, float x2, float y2,
                           DXCOLOR color, int FillFlag);
extern DXCALL int DrawFillBox(int x1, int y1, int x2, int y2,
                              DXCOLOR color);
extern DXCALL int DrawFillBoxF(float x1, float y1, float x2, float y2,
                               DXCOLOR color);
extern DXCALL int DrawLineBox(int x1, int y1, int x2, int y2,
                              DXCOLOR color);
extern DXCALL int DrawLineBoxF(float x1, float y1, float x2, float y2,
                               DXCOLOR color);

// - Draws a circle centered at (x,y), with radius r.
extern DXCALL int DrawCircle(int x, int y, int r,
                             DXCOLOR color, int fillFlag);
extern DXCALL int DrawCircleF(float x, float y, float r,
                              DXCOLOR color, int fillFlag);
// - Draws an ellipse centered at (x,y), with extents (rx,ry).
extern DXCALL int DrawOval(int x, int y, int rx, int ry,
                           DXCOLOR color, int fillFlag);
extern DXCALL int DrawOvalF(float x, float y, float rx, float ry,
                            DXCOLOR color, int fillFlag);

// - Draws a triangle at the given coordinates.
extern DXCALL int DrawTriangle(int x1, int y1, int x2, int y2,
                               int x3, int y3,
                               DXCOLOR color, int fillFlag);
extern DXCALL int DrawTriangleF(float x1, float y1, float x2, float y2,
                                float x3, float y3,
                                DXCOLOR color, int fillFlag);
extern DXCALL int DrawQuadrangle(int x1, int y1, int x2, int y2,
                                 int x3, int y3, int x4, int y4,
                                 DXCOLOR color, int fillFlag);
extern DXCALL int DrawQuadrangleF(float x1, float y1, float x2, float y2,
                                  float x3, float y3, float x4, float y4,
                                  DXCOLOR color, int fillFlag);

// - Draws a graph whole to at (x,y).
extern DXCALL int DrawGraph(int x, int y, int graphID, int blendFlag);
extern DXCALL int DrawGraphF(float x, float y, int graphID, int blendFlag);

// - Draws a graph whole from (x1,y1) to (x2,y2).
extern DXCALL int DrawExtendGraph(int x1, int y1, int x2, int y2,
                                  int graphID, int blendFlag);
extern DXCALL int DrawExtendGraphF(float x1, float y1, float x2, float y2,
                                   int graphID, int blendFlag);
                     
// - Draws a subsection of the graph
//   (sx, sy, sx+sw, sy+sh) to (dx,dy).
extern DXCALL int DrawRectGraph(int dx, int dy,
                                int sx, int sy, int sw, int sh,
                                int graphID, int blendFlag, int turnFlag);
extern DXCALL int DrawRectGraphF(float dx, float dy,
                                 int sx, int sy, int sw, int sh,
                                 int graphID, int blendFlag, int turnFlag);

// - Draws a subsection of the graph
//   (sx, sy, sx+sw, sy+sh) to (dx1,dy1,dx2,dy2).
extern DXCALL int DrawRectExtendGraph(
                               int dx1, int dy1, int dx2, int dy2,
                               int sx, int sy, int sw, int sh,
                               int graphID, int blendFlag, int turnFlag);
extern DXCALL int DrawRectExtendGraphF(
                               float dx1, float dy1, float dx2, float dy2,
                               int sx, int sy, int sw, int sh,
                               int graphID, int blendFlag, int turnFlag);

// - Draws the graph rotated from (x,y), with graph center point (cx,cy),
//   and scales by (scaleFactorX, scaleFactorY).
// (cx,cy) defaults to the graph's center.
// For functions where they are not separate, both scaleFactors are equal.
extern DXCALL int DrawRotaGraph(int x, int y,
                                double scaleFactor, double angle,
                                int graphID, int blendFlag,
                                int turn = DXFALSE);
extern DXCALL int DrawRotaGraphF(float x, float y,
                                 double scaleFactor, double angle,
                                 int graphID, int blendFlag,
                                 int turn = DXFALSE);
extern DXCALL int DrawRotaGraph2(int x, int y, int cx, int cy,
                                 double scaleFactor, double angle,
                                 int graphID, int blendFlag,
                                 int turn = DXFALSE);
extern DXCALL int DrawRotaGraph2F(float x, float y, float cx, float cy,
                                  double scaleFactor, double angle,
                                  int graphID, int blendFlag,
                                  int turn = DXFALSE);
extern DXCALL int DrawRotaGraph3(int x, int y, int cx, int cy,
                                 double xScaleFactor, double yScaleFactor,
                                 double angle, int graphID, int blendFlag,
                                 int turn = DXFALSE);
extern DXCALL int DrawRotaGraph3F(float x, float y, float cx, float cy,
                                  double xScaleFactor, double yScaleFactor,
                                  double angle, int graphID, int blendFlag,
                                  int turn = DXFALSE);

// - Draws a section of a graph (sx, sy, sx+sw, sy+sh)
//   rotated from (x,y), with graph center point (cx,cy),
//   and scales by (scaleFactorX, scaleFactorY).
// (cx,cy) defaults to the graph's center.
// For functions where they are not separate, both scaleFactors are equal.
extern DXCALL int DrawRectRotaGraph(int x, int y, 
                          int sx, int sy, int sw, int sh,
                          double scaleFactor, double angle,
                          int graphID, int blendFlag, int turn);
extern DXCALL int DrawRectRotaGraphF(float x, float y,
                           int sx, int sy, int sw, int sh,
                           double scaleFactor, double angle,
                           int graphID, int blendFlag, int turn);
extern DXCALL int DrawRectRotaGraph2(int x, int y, int cx, int cy,
                           int sx, int sy, int sw, int sh,
                           double scaleFactor, double angle,
                           int graphID, int blendFlag, int turn);
extern DXCALL int DrawRectRotaGraph2F(float x, float y,
                            int sx, int sy, int sw, int sh,
                            float cx, float cy,
                            double scaleFactor, double angle,
                            int graphID, int blendFlag, int turn);
extern DXCALL int DrawRectRotaGraph3(int x, int y,
                           int sx, int sy, int sw, int sh,
                           int cx, int cy,
                           double xScaleFactor, double yScaleFactor,
                           double angle,
                           int graphID, int blendFlag, int turn);
extern DXCALL int DrawRectRotaGraph3F(float x, float y,
                            int sx, int sy, int sw, int sh,
                            float cx, float cy,
                            double xScaleFactor, double yScaleFactor,
                            double angle,
                            int graphID, int blendFlag, int turn);

// - Draws a horizontally flipped graph to (x,y).
extern DXCALL int DrawTurnGraph(int x, int y,
                                int graphID, int blendFlag);
extern DXCALL int DrawTurnGraphF(float x, float y,
                                 int graphID, int blendFlag);

// - Draws a graph to the given quad.
extern DXCALL int DrawModiGraph(int x1, int y1, int x2, int y2,
                                int x3, int y3, int x4, int y4,
                                int graphID, int blendFlag);
extern DXCALL int DrawModiGraphF(float x1, float y1, float x2, float y2,
                                 float x3, float y3, float x4, float y4,
                                 int graphID, int blendFlag);

// - Clips the drawable area of the screen to (x1, y1, x2, y2).
extern DXCALL int SetDrawArea(int x1, int y1, int x2, int y2);

// - Sets the current texture filtering mode from DX_DRAWMODE_*
extern DXCALL int SetDrawMode(int drawMode);
extern DXCALL int GetDrawMode();

// - Sets the current blending mode from DX_BLENDMODE_*
extern DXCALL int SetDrawBlendMode(int blendMode, int alpha);
extern DXCALL int GetDrawBlendMode(int *blendMode, int *alpha);

// - Sets the drawing color, which all displayed colors are multiplied by.
extern DXCALL int SetDrawBright(int redBright,
                                int greenBright,
                                int blueBright);

// - Uses simple blending for software mode.
// NOTICE: This does nothing, as software rendering is not supported.
extern DXCALL int SetBasicBlendFlag(int blendFlag);

// - Sets background color for use with ClearDrawScreen.
extern DXCALL int SetBackgroundColor(int red, int green, int blue);

// - Clears the current screen. If clearRect is NULL, clears whole screen.
extern DXCALL int ClearDrawScreen(const RECT *clearRect = NULL);
extern DXCALL int ClsDrawScreen();

// - Saves a region of the current screen to an image file.
extern DXCALL int SaveDrawScreen(int x1, int y1, int x2, int y2,
                                 const DXCHAR *filename,
                                 int saveType = DX_IMAGESAVETYPE_BMP,
                                 int jpegQuality = 80,
                                 int jpegSample2x1 = DXTRUE,
                                 int pngCompressionLevel = -1);
extern DXCALL int SaveDrawScreenToBMP(int x1, int y1, int x2, int y2,
                                      const DXCHAR *filename);
extern DXCALL int SaveDrawScreenToJPEG(int x1, int y1, int x2, int y2,
                                       const DXCHAR *filename,
                                       int quality = 80,
                                       int sample2x1 = DXTRUE);
extern DXCALL int SaveDrawScreenToPNG(int x1, int y1, int x2, int y2,
                                      const DXCHAR *filename,
                                      int compressionLevel = -1);

// - Given the three RGB components, returns a color value.
extern DXCALL DXCOLOR GetColor(int red, int green, int blue);

// ------------------------------------------------------------- DxFont.cpp
#ifndef DX_NON_FONT

// - DxPortLib Extension.
//   Given a .ttf filename, it will 'map' that .ttf to a fontname,
//   a minimum thickness value, and a flag for whether or not the font is
//   bolded.
//   exRateX/exRateY are a global Extend multiplier used.
// NOTICE: This must be used for all fonts.
extern DXCALL int EXT_MapFontFileToName(const DXCHAR *filename,
                                        const DXCHAR *fontname,
                                        int thickness,
                                        int boldFlag,
                                        double exRateX = 1.0,
                                        double exRateY = 1.0
                                        );
// - DxPortLib Extension.
//   Deletes all existing font mappings.
//   Will not delete font handles.
extern DXCALL int EXT_InitFontMappings();

// ------ Font handle functions

// - Draws a string at the given position, with the given font and color.
extern DXCALL int DrawStringToHandle(int x, int y, const DXCHAR *string,
                                     DXCOLOR color, int fontHandle,
                                     DXCOLOR edgeColor = 0);
extern DXCALL int DrawFormatStringToHandle(
                                     int x, int y, DXCOLOR color,
                                     int fontHandle,
                                     const DXCHAR *formatString, ...);
// - Draws a scaled string at the given position, with the given font/color.
extern DXCALL int DrawExtendStringToHandle(double ExRateX,
                                           double ExRateY,
                                           int x, int y,
                                           const DXCHAR *string,
                                           DXCOLOR color,
                                           int fontHandle,
                                           DXCOLOR edgeColor = 0);
extern DXCALL int DrawExtendFormatStringToHandle(
                                           double ExRateX,
                                           double ExRateY,
                                           int x, int y,
                                           DXCOLOR color,
                                           int fontHandle,
                                           const DXCHAR *formatString,
                                           ...);

// - Gets the width of a string that would be drawn.
extern DXCALL int GetDrawStringWidthToHandle(const DXCHAR *string,
                                             int strLen, int fontHandle);
extern DXCALL int GetDrawFormatStringWidthToHandle(int fontHandle,
                                                   const DXCHAR *string,
                                                   ...);
// - Gets the scaled width of a string that would be drawn.
extern DXCALL int GetDrawExtendStringWidthToHandle(double ExRateX,
                                                   const DXCHAR *string,
                                                   int strLen,
                                                   int fontHandle);
extern DXCALL int GetDrawExtendFormatStringWidthToHandle(
                                                   double ExRateX,
                                                   int fontHandle,
                                                   const DXCHAR *string,
                                                   ...);

// - Gets the font handle's size.
extern DXCALL int GetFontSizeToHandle(int fontHandle);

// - Gets the dimensions and advance information of the first
//   character of the given string.
extern DXCALL int GetFontCharInfo(int fontHandle, const DXCHAR *string,
                                  int *xPos, int *yPos, int *advanceX,
                                  int *width, int *height);

// - Sets the spacing between characters for a font handle.
// Negative values are valid.
// Does not refresh font information so there is no performance cost.
extern DXCALL int SetFontSpaceToHandle(int fontSpacing, int fontHandle);

// - Creates a font handle.
// NOTICE: Use EXT_MapFontFileToName to map ttf files to font names.
// fontType is one of DX_FONTTYPE_*.
//   Default fontType DX_FONTTYPE_NORMAL.
// thickness selects a mapping, but has no other purpose.
//   Default thickness is 6.
// charset is the character set to use for this handle.
//   -1 or DX_CHARSET_DEFAULT uses the current charset.
// edgeSize is valid for DX_FONTTYPE*_EDGE and may be 1 through 4.
//   Default edgeSize is 1.
// italics draws the font italicized. defualt is DXFALSE.
extern DXCALL int CreateFontToHandle(const DXCHAR *fontname,
                                     int size, int thickness = -1,
                                     int fontType = -1, int charset = -1,
                                     int edgeSize = -1, int italic = DXFALSE
                                     );
// - Deletes a font handle.
extern DXCALL int DeleteFontToHandle(int handle);
// - Returns TRUE if a font handle is still valid.
extern DXCALL int CheckFontHandleValid(int fontHandle);
// - When the font handle has been deleted, sets lostFlag to -1.
extern DXCALL int SetFontLostFlag(int fontHandle, int *lostFlag);

// - Deletes all font handles.
extern DXCALL int InitFontToHandle();

// ------ "Default" font functions
// DxPortLib maintains a font handle internally for the default font.
// NOTICE: Unliked DxLib, there is no font set by default!
// 
// Changing any font information will cause it to refresh that font handle
// the next time it is used, which is slow.
//
// DxPortLib will use this default font internally for anything that
// requires one, such as the DxLog functions.
//
// You should set this only once in your program and then use handles
// for everything else.

// - Draws a string with the default font to (x,y).
extern DXCALL int DrawString(int x, int y,
                             const DXCHAR *string,
                             DXCOLOR color, DXCOLOR edgeColor = 0);
extern DXCALL int DrawFormatString(int x, int y,
                                   DXCOLOR color,
                                   const DXCHAR *formatString, ...);

// - Draws a scaled string with the default font.
extern DXCALL int DrawExtendString(int x, int y,
                                   double ExRateX, double ExRateY,
                                   const DXCHAR *string,
                                   DXCOLOR color, DXCOLOR edgeColor = 0);
extern DXCALL int DrawExtendFormatString(int x, int y,
                                         double ExRateX, double ExRateY,
                                         DXCOLOR color,
                                         const DXCHAR *formatString, ...);

// - Gets the width of a string using the default font.
extern DXCALL int GetDrawStringWidth(const DXCHAR *string, int strLen);
extern DXCALL int GetDrawFormatStringWidth(const DXCHAR *string, ...);

// - Gets the scaled width of a string using the default font.
extern DXCALL int GetDrawExtendStringWidth(double ExRateX,
                                           const DXCHAR *string,
                                                 int strLen);
extern DXCALL int GetDrawExtendFormatStringWidth(double ExRateX,
                                                 const DXCHAR *string, ...);

// - Changes the default font and charset.
extern DXCALL int ChangeFont(const DXCHAR *fontName, int charSet = -1);
// - Changes the default font type.
extern DXCALL int ChangeFontType(int fontType);

// - Changes the default font size.
extern DXCALL int SetFontSize(int fontSize);
// - Gets the default font's size.
extern DXCALL int GetFontSize();
// - Sets the default font's thickness.
extern DXCALL int SetFontThickness(int fontThickness);
// - Sets the default font's spacing.
extern DXCALL int SetFontSpace(int fontSpace);
// - Sets the default font's name, size, and thickness all at once.
extern DXCALL int SetDefaultFontState(const DXCHAR *fontName,
                                      int fontSize, int fontThickness);

// - Gets the current default font handle.
// NOTICE: This will change if the font is changed.
extern DXCALL int GetDefaultFontHandle();

#endif /* #ifndef DX_NON_FONT */

// ------------------------------------------------------------ DxAudio.cpp
#ifndef DX_NON_SOUND

// - Plays a given sound handle.
// If DX_PLAYTYPE_NORMAL is used, it will wait until the sound finished.
// If DX_PLAYTYPE_BACK is used, it will play the sound in the background.
// If DX_PLAYTYPE_LOOP is set, it will loop until it is stopped.
// If startPositionFlag is TRUE, it will reset the sound's current position.
extern DXCALL int PlaySoundMem(int soundID, int playType, 
                               int startPositionFlag = DXTRUE);

// - Stops the playback of a sound handle.
extern DXCALL int StopSoundMem(int soundID);

// - Returns TRUE if a sound handle is playing.
extern DXCALL int CheckSoundMem(int soundID);

// - Sets the volume of the sound in decibels from -10000 to 0.
extern DXCALL int SetVolumeSoundMem(int volume, int soundID);
// - Sets the volume of the sound linearly from 0 to 255.
extern DXCALL int ChangeVolumeSoundMem(int volume, int soundID);
// - If TRUE, uses the older (incorrect) volume calculation mode.
// Default: FALSE.
extern DXCALL int SetUseOldVolumeCalcFlag(int volumeFlag);

// - Loads a sound file, returning a playable handle.
// WAV files are loaded whole, OGG files are streamed.
extern DXCALL int LoadSoundMem(const DXCHAR *filename);
// - Loads two sound files, an intro segment and then a second segment.
// If this is played with DX_PLAYTYPE_LOP, only the second part will loop.
extern DXCALL int LoadSoundMem2(const DXCHAR *filename,
                                const DXCHAR *filename2);

// - Deletes a sound handle.
extern DXCALL int DeleteSoundMem(int soundID);

// - Deletes all sound handles.
extern DXCALL int InitSoundMem();

// - Sets the data storage type for loaded sounds.
// NOTICE: DxPortLib currently only supports DX_SOUNDDATATYPE_MEMNOPRESS.
extern DXCALL int SetCreateSoundDataType(int soundDataType);
extern DXCALL int GetCreateSoundDataType();

#endif /* #ifndef DX_NON_SOUND */

// ----------------------------------------------------------- DxMemory.cpp
// NOTICE: DxPortLib does not actually use file/line at this time.

// - Allocates allocationSize bytes of memory.
extern DXCALL void * DxAlloc(size_t allocationSize,
                             const char *file = NULL, int line = -1);
// - Allocates allocationSize bytes of memory, and zeroes them out.
extern DXCALL void * DxCalloc(size_t allocationSize,
                              const char *file = NULL, int line = -1);
// - Resizes a block of memory, returning the pointer to its new location.
//   The previous pointer is released and becomes invalid.
extern DXCALL void * DxRealloc(void *memory, size_t allocationSize,
                               const char *file = NULL, int line = -1);
// - Frees a block of memory.
extern DXCALL void DxFree(void *memory);

};

// ------------------------------------------------------------------
// Set DxLib as a default namespace, like the original library.

using namespace DxLib;

#endif
