//---------------------------------------------------------------------------

#ifndef Main_UH
#define Main_UH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sSkinManager.hpp"
#include <IOUtils.hpp>
#include <libzplay.h>
#include "sSpeedButton.hpp"
#include <Vcl.Buttons.hpp>
#include "acNoteBook.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "sBitBtn.hpp"
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include "sCustomComboEdit.hpp"
#include "sListView.hpp"
#include "sMaskEdit.hpp"
#include "sToolEdit.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "sStatusBar.hpp"
#include "sLabel.hpp"
#include "sTrackBar.hpp"
#include "acImage.hpp"
#include "acPNG.hpp"
#include "acAlphaImageList.hpp"
#include <Vcl.ImgList.hpp>
#include "acSlider.hpp"
#include "sPanel.hpp"
#include "sComboBoxes.hpp"
#include "acProgressBar.hpp"
#include <Vcl.Graphics.hpp>
#include <string>

using namespace libZPlay;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TsSkinManager *Skin;
	TsSpeedButton *Play_Button;
	TsSpeedButton *Pause_Button;
	TsSpeedButton *Stop_Button;
	TsSpeedButton *Previous_Button;
	TsSpeedButton *Next_Button;
	TMainMenu *Menu;
	TMenuItem *C1;
	TMenuItem *O2;
	TMenuItem *S1;
	TMenuItem *A1;
	TMenuItem *E1;
	TMenuItem *N1;
	TMenuItem *N2;
	TsDirectoryEdit *Folder;
	TsListView *List_Songs;
	TsStatusBar *sStatusBar1;
	TsLabel *Folder_Label;
	TsLabel *Current_Label;
	TsLabel *Time_Label;
	TsTrackBar *tbVolume;
	TsSpeedButton *btnVolume;
	TsAlphaImageList *imgVolume;
	TsTrackBar *tbSong;
	TsLabel *Time_Label2;
	TTimer *Timer_tb;
	TsSpeedButton *btn_FastBackward;
	TsSpeedButton *btn_FastForward;
	TsSpeedButton *Shuffle_Button;
	TsLabel *lbMode;
	TsImage *imgBackground;
	TsImage *imgBackground2;
	void __fastcall E1Click(TObject *Sender);
	void __fastcall O2Click(TObject *Sender);
	void __fastcall FolderChange(TObject *Sender);
	void __fastcall List_SongsDblClick(TObject *Sender);
	void __fastcall A1Click(TObject *Sender);
	void __fastcall Next_ButtonClick(TObject *Sender);
	void __fastcall Previous_ButtonClick(TObject *Sender);
	void __fastcall Play_ButtonClick(TObject *Sender);
	void __fastcall Stop_ButtonClick(TObject *Sender);
	void __fastcall Pause_ButtonClick(TObject *Sender);
	void __fastcall tbVolumeChange(TObject *Sender);
	void __fastcall btnVolumeClick(TObject *Sender);
	void __fastcall Timer_tbTimer(TObject *Sender);
	void __fastcall btn_FastForwardClick(TObject *Sender);
	void __fastcall btn_FastBackwardClick(TObject *Sender);
	void __fastcall Shuffle_ButtonClick(TObject *Sender);
	void __fastcall tbSongUserChange(TObject *Sender);



private:	// User declarations
public:		// User declarations
	int currentIndex;
	__fastcall TForm1(TComponent* Owner);
	TStringList *list_Files;  //TStringList jest klas¹ s³u¿¹c¹ do uporz¹dkowanego umieszczenia obiektów typu String na liœcie
	TListItem *itm;
							// Elementy klasy TListView
	ZPlay *player;
	TID3InfoEx metadata;
	TStreamInfo songInfo;
	TStreamTime pos;
	TStreamStatus status;
	TStreamTime pTime;
	void generateMetadata(String fileName);
	void playThis(int index);
	void Duration (obiekt);
	static String* GetFileNameWithoutExtension(String* path);
	void playMode(int mode);
	void songTime();
	void currentLabel();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
