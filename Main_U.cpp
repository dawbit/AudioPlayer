//---------------------------------------------------------------------------

#include <vcl.h>
#include "Shlwapi.h"
#include <stdlib.h>
#include <ctime>
#pragma hdrstop

#include "Main_U.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sSkinManager"
#pragma link "sSpeedButton"
#pragma link "acNoteBook"
#pragma link "sBitBtn"
#pragma link "sCustomComboEdit"
#pragma link "sListView"
#pragma link "sMaskEdit"
#pragma link "sToolEdit"
#pragma link "sStatusBar"
#pragma link "sLabel"
#pragma link "sTrackBar"
#pragma link "acImage"
#pragma link "acPNG"
#pragma link "acAlphaImageList"
#pragma link "acSlider"
#pragma link "sPanel"
#pragma link "sComboBoxes"
#pragma link "acProgressBar"
#pragma resource "*.dfm"
#pragma comment(lib, "libzplay_borland.lib")
TForm1 *Form1;


int a=1, currentIndex, previousIndex;
bool mode=false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	list_Files=new TStringList;
	list_Files->Clear();

	player=CreateZPlay();
	player->SetPlayerVolume(50,50);
	tbVolume->Position=50;
	lbMode->Caption="OFF";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::E1Click(TObject *Sender)
{
	 Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::O2Click(TObject *Sender)
{
	Folder->Button->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FolderChange(TObject *Sender)
{
	  Folder_Label->Caption=Folder->Text;
	  TStringDynArray arr=TDirectory::GetFiles(Folder->Text);

	  for (int i=0; i<arr.Length; i++)                                           /// DODAJE TYLKO MP3 I WAV
	  {
		 if(ExtractFileExt(arr[i]).LowerCase()==".mp3" || ExtractFileExt(arr[i]).LowerCase()==".wav" || ExtractFileExt(arr[i]).LowerCase()==".aac" || ExtractFileExt(arr[i]).LowerCase()==".flac")
		 {
			 list_Files->Add(arr[i]);
			 generateMetadata(arr[i]);
			 itm=List_Songs->Items->Add();
			 itm->Caption=a; a++;
			 if (ExtractFileExt(arr[i]).LowerCase()==".flac") itm->SubItems->Add(ExtractFileName(arr[i]).Delete(ExtractFileName(arr[i]).Length()-4,5));
			 else itm->SubItems->Add(ExtractFileName(arr[i]).Delete(ExtractFileName(arr[i]).Length()-3,4));

			   player->GetStreamInfo(&songInfo);

			   int min = songInfo.Length.hms.minute;
			   int sec = songInfo.Length.hms.second;

			   if (sec<10) {
					itm->SubItems->Add(IntToStr(min)+":"+0+IntToStr(sec));
			   } else itm->SubItems->Add(IntToStr(min)+":"+IntToStr(sec));
		 }
	  }

	  List_Songs->Enabled=true;
	  Previous_Button->Enabled=true;
	  Next_Button->Enabled=true;
	  Play_Button->Enabled=true;
	  Pause_Button->Enabled=true;
	  Stop_Button->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::List_SongsDblClick(TObject *Sender)
{
		if(List_Songs->ItemIndex >=0)
		{
		 currentIndex=List_Songs->ItemIndex;
		 playThis(List_Songs->ItemIndex);
		}

	  List_Songs->ItemIndex=currentIndex;
	  playThis(currentIndex);
	if(List_Songs->ItemIndex>=0)
	{
	   generateMetadata(list_Files->Strings[List_Songs->ItemIndex]);
	   currentLabel();
	   player->Play();

		songTime();
	}
}
//---------------------------------------------------------------------------

void TForm1::generateMetadata(String fileName)
{
	if(player->OpenFileW(fileName.c_str(),sfAutodetect))      ///prawid³owo otwarty plik
	{
	}
	if(player->LoadID3Ex(&metadata,1))                       /// mamy metadate
	{
	}
}


void __fastcall TForm1::A1Click(TObject *Sender)
{
	ShowMessage("\tOdtwarzacz audio \t\n\tWykonanie:\t\n\tKrupa Marcin / Bitner Dawid\t\n\tProjekt 2017/18\t");
}
//---------------------------------------------------------------------------

void TForm1::playThis(int index){
	generateMetadata(list_Files->Strings[index]);
	player->Play();
	Timer_tb->Enabled=true;
}


void __fastcall TForm1::Next_ButtonClick(TObject *Sender)
{
	playMode(mode);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Previous_ButtonClick(TObject *Sender)
{
	if (mode==false) {
	if (currentIndex==0) {
		currentIndex=a-2;
		} else currentIndex=currentIndex-1;
		} else currentIndex=previousIndex;
	List_Songs->ItemIndex=currentIndex;

currentLabel();

  playThis(currentIndex);
  songTime();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Play_ButtonClick(TObject *Sender)
{
	if (Timer_tb->Enabled==false)
	{
		player->Play();
		Timer_tb->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Stop_ButtonClick(TObject *Sender)
{
	Timer_tb->Enabled=false;
	player->Stop();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Pause_ButtonClick(TObject *Sender)
{
	if (Timer_tb->Enabled==true)
	{
		Timer_tb->Enabled=false;
		player->Pause();
	} else {
		Timer_tb->Enabled=true;
		player->Play();
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::tbVolumeChange(TObject *Sender)
{
	player->SetPlayerVolume(tbVolume->Position,tbVolume->Position);

	if (tbVolume->Position == 0) {
	 btnVolume->ImageIndex=0;
	} else if (tbVolume->Position > 0 && tbVolume->Position < 50) btnVolume->ImageIndex=2;
	else btnVolume->ImageIndex=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnVolumeClick(TObject *Sender)
{
	if(tbVolume->Visible==True) tbVolume->Visible=False;
	else if(tbVolume->Visible==False) tbVolume->Visible=True;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer_tbTimer(TObject *Sender)
{
	player->GetPosition(&pos);

	int min = pos.hms.minute;
	int sec = pos.hms.second;
	if (sec<10) {
		Time_Label2->Caption=IntToStr(min)+":"+0+IntToStr(sec);
	} else Time_Label2->Caption=IntToStr(min)+":"+IntToStr(sec);

	tbSong->Position=60*pos.hms.minute+pos.hms.second;
	player->GetStatus(&status);
	if (!(status.fPlay))
	{
	   playMode(mode);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btn_FastForwardClick(TObject *Sender)
{
	pTime.sec = 10;
		player->Seek(tfSecond, &pTime, smFromCurrentForward);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btn_FastBackwardClick(TObject *Sender)
{
	pTime.sec = 10;
		player->Seek(tfSecond, &pTime, smFromCurrentBackward);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbSongUserChange(TObject *Sender)
{
	Timer_tb->Enabled=false;
	int pozycja=tbSong->Position;
	int min=pozycja/60;
	int sec=pozycja%60;

	if (sec<10) {
		Time_Label2->Caption=IntToStr(min)+":"+0+IntToStr(sec);
	} else Time_Label2->Caption=IntToStr(min)+":"+IntToStr(sec);

	player->GetPosition(&pos);
	int pozycja2=pos.hms.minute*60+pos.hms.second;
	int lolissimo=pozycja-pozycja2;
	if (lolissimo>0) {
		pTime.sec = lolissimo;
	   player->Seek(tfSecond, &pTime, smFromCurrentForward);
	} else {
	   pTime.sec = pozycja-pozycja2;
	   player->Seek(tfSecond, &pTime, smFromCurrentBackward);
	}
	Timer_tb->Enabled=true;
}
//---------------------------------------------------------------------------

void TForm1::playMode(int mode)
{
	previousIndex=currentIndex;
	if (mode==false) {
		if (currentIndex==a-2) {
		  currentIndex=0;
		} else currentIndex++;
		List_Songs->ItemIndex=currentIndex;
		currentLabel();
		playThis(currentIndex);
	} else {
		srand(time(NULL));
		currentIndex=0+rand()%(a);
		List_Songs->ItemIndex=currentIndex;
		currentLabel();
		playThis(currentIndex);
	}
	songTime();
}

void TForm1::songTime()
{
	player->GetStreamInfo(&songInfo);
	int min = songInfo.Length.hms.minute;
	int sec = songInfo.Length.hms.second;

	if (sec<10) {
		Time_Label->Caption=IntToStr(min)+":"+0+IntToStr(sec);
	} else Time_Label->Caption=IntToStr(min)+":"+IntToStr(sec);
	tbSong->Max=min*60+sec;
}

void TForm1::currentLabel()
{
		if (ExtractFileExt(list_Files->Strings[List_Songs->ItemIndex]).LowerCase()==".flac") Current_Label->Caption=ExtractFileName(list_Files->Strings[List_Songs->ItemIndex]).Delete(ExtractFileName(list_Files->Strings[List_Songs->ItemIndex]).Length()-4,5);
		else Current_Label->Caption=ExtractFileName(list_Files->Strings[List_Songs->ItemIndex]).Delete(ExtractFileName(list_Files->Strings[List_Songs->ItemIndex]).Length()-3,4);
}

void __fastcall TForm1::Shuffle_ButtonClick(TObject *Sender)
{
	if (mode==false){
		mode=true;
		lbMode->Caption="ON";
	} else {
		mode=false;
		lbMode->Caption="OFF";
	}
}
//---------------------------------------------------------------------------

