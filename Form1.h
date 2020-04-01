#pragma once

#pragma warning (disable: 4244)

#define TMAX 100
#define PMAX 200

#include "RotateImage.h"
#include "SDialog.h"

namespace LaserTanks
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::IO;

	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			InitializeComponent();
			U1 = Forms::Keys::Up;
			L1 = Forms::Keys::Left;
			R1 = Forms::Keys::Right;
			D1 = Forms::Keys::Down;
			ST1 = Forms::Keys::NumPad0;
			RC1 = Forms::Keys::NumPad2;
			RA1 = Forms::Keys::NumPad1;
			S1 = Forms::Keys::ControlKey;
			P1 = Forms::Keys::P;
			U2 = Forms::Keys::W;
			L2 = Forms::Keys::A;
			R2 = Forms::Keys::D;
			D2 = Forms::Keys::S;
			ST2 = Forms::Keys::V;
			RC2 = Forms::Keys::H;
			RA2 = Forms::Keys::G;
			S2 = Forms::Keys::Space;
			P2 = Forms::Keys::F4;
			spawn_x = new float __gc[TMAX];
			spawn_y = new float __gc[TMAX];
			x = new float __gc[TMAX];
			y = new float __gc[TMAX];
			dx = new float __gc[TMAX];
			dy = new float __gc[TMAX];
			init_d = new int __gc[TMAX];
			td = new int __gc[TMAX];
			hp = new int __gc[TMAX];
			dd = new int __gc[TMAX];
			sd = new int __gc[TMAX];
			ammo = new int __gc[TMAX];
			hs = new int __gc[TMAX];
			team = new int __gc[TMAX];
			tgt = new int __gc[TMAX];
			stance = new int __gc[TMAX];
			disp = new int __gc[TMAX];
			dmax = new int __gc[TMAX];
			d_tgt = new bool __gc[TMAX];
			d_stance = new bool __gc[TMAX];
			exists = new bool __gc[TMAX];
			ai = new bool __gc[TMAX];
			recoil = new int __gc[TMAX];
			px1 = new float __gc[PMAX];
			for (int i = 0; i < PMAX; i++)
				px1[i] = -32;
			px2 = new float __gc[PMAX];
			py1 = new float __gc[PMAX];
			py2 = new float __gc[PMAX];
			pro_s = new int __gc[PMAX];
			pd = new int __gc[PMAX];
			xl = sx/2 + 8;
			xr = this->Width - 24 - sx/2;
			yt = sy/2 + 18;
			yb = this->Height - 48 - sy/2;
			t_img = new System::Drawing::Image * __gc[TMAX];
			for (int i = 0; i < TMAX; i++)
				t_img[i] = TankImage->Images->get_Item(0);
			tu_img = TurretImage->Images->get_Item(0);
			cs = new System::Drawing::Color __gc[TMAX];
			for (int i = 0; i < TMAX; i++)
				cs[i] = Color::DarkGray;
			cs[0] = Color::DodgerBlue;
			cs[1] = Color::OrangeRed;
			cs[2] = Color::Lime;
			cs[3] = Color::Yellow;
			try
			{
				fs = new FileStream(String::Concat(Environment::CurrentDirectory, "\\NoCursor.cur"), FileMode::Open);
				cur = new Forms::Cursor(fs);
			}
			catch (Exception * ex)
			{
				MessageBox::Show(String::Concat("Error: Unable to load blank cursor file!\n\n", ex->ToString()), "LaserTanks", MessageBoxButtons::OK, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button1);
				cur = Cursors::Default;
			}
			bmp = new Bitmap(this->Width, this->Height);
		}
  
	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	private: 
		// Variables
		int U1, L1, R1, D1, ST1, RC1, RA1, S1, P1; // ULRD - Stop - Rotate c'wise/a-c'wise - Shoot - Pause
		int U2, L2, R2, D2, ST2, RC2, RA2, S2, P2;
		float xl, xr, yt, yb;
		int at, ct, ex, ey; // Victor index - current tank (edit mode) - mouse location-x/y (edit mode)
		static bool PauseState = false, EditMode = false;
		static int GameEnding = -1, tMax = 4, pMax = 8;
		static Random * r = new Random();
		System::Drawing::Image * tu_img;
		System::Windows::Forms::Cursor * cur;
		System::IO::FileStream * fs;
		// Variable arrays
		float spawn_x __gc[], spawn_y[], x[], y[], dx[], dy[]; // spawns - locations - location changes
		int init_d __gc[]; // initial directions
		int td __gc[], hp[], dd[], sd[]; // turret directions - hitpoints - direction changes - shot delays
		int ammo __gc[], pro_s[], pd[], recoil[]; // pro_s = projectile state, pd = projectile direction
		int hs __gc[], team[]; // show health - team ID
		float px1 __gc[], py1[], px2[], py2[]; // projectile-x/y1, x/y2
		int tgt __gc[], stance[], disp[]; // AI's randomly updated variables: target - stance - dispersion
		int dmax __gc[];  // AI only - max. dispersion
		bool d_tgt __gc[], d_stance[];
		bool exists __gc[], ai[];
		System::Drawing::Image * t_img __gc[];
		System::Drawing::Bitmap * bmp;
		System::Drawing::Color cs __gc[];
		// Static variables (can only be modified in game settings)
		static int hpi = 10, sdi = 50, rlt = 150, crs = 6; // max HP - shot delay - reload time - cartridge size
		static int rec = 8, d_max = 6, ds = 2, ffs = 0, st = 0; // recoil time - AI max dispersion - difficulty setting - friendly fire setting - selected tab
		static bool gsd = true; // default general settings
		static double hpr = 1, dcr = 0.1; // - AI/human HP ratio - AI direction change rate
		// Constants
		static const int sx = 31, sy = 35, sp = 4, dsp = 3; // tank size-x/y - speed - diagonal speed
		static const int rs = 4, ht = 65; // rotate speed - health display time

	private: System::Windows::Forms::Timer *  GameLoop;
	private: System::Windows::Forms::ImageList *  TankImage;
	private: System::Windows::Forms::ImageList *  TurretImage;
	private: System::Windows::Forms::Label *  Start1P;
	private: System::Windows::Forms::Label *  Start2P;
private: System::Windows::Forms::Label *  VictoryLabel;
private: System::Windows::Forms::Timer *  VictorySFX;
private: System::Windows::Forms::Label *  Simulate;
private: System::Windows::Forms::Label *  Settings;
private: System::Windows::Forms::Timer *  FastLoop;
private: System::Windows::Forms::Timer *  EditorLoop;
private: System::Windows::Forms::Label *  P2Label;
private: System::Windows::Forms::Label *  P1Label;
private: System::Windows::Forms::Label *  P4Label;
private: System::Windows::Forms::Label *  P3Label;
private: System::Windows::Forms::Label *  P3Title;
private: System::Windows::Forms::Label *  P4Title;
private: System::Windows::Forms::Label *  P2Title;
private: System::Windows::Forms::Label *  P1Title;


	private: System::ComponentModel::IContainer *  components;

	private:
		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(LaserTanks::Form1));
			this->GameLoop = new System::Windows::Forms::Timer(this->components);
			this->TankImage = new System::Windows::Forms::ImageList(this->components);
			this->TurretImage = new System::Windows::Forms::ImageList(this->components);
			this->Start1P = new System::Windows::Forms::Label();
			this->Start2P = new System::Windows::Forms::Label();
			this->VictoryLabel = new System::Windows::Forms::Label();
			this->VictorySFX = new System::Windows::Forms::Timer(this->components);
			this->Settings = new System::Windows::Forms::Label();
			this->Simulate = new System::Windows::Forms::Label();
			this->FastLoop = new System::Windows::Forms::Timer(this->components);
			this->EditorLoop = new System::Windows::Forms::Timer(this->components);
			this->P2Label = new System::Windows::Forms::Label();
			this->P1Label = new System::Windows::Forms::Label();
			this->P4Label = new System::Windows::Forms::Label();
			this->P3Label = new System::Windows::Forms::Label();
			this->P3Title = new System::Windows::Forms::Label();
			this->P4Title = new System::Windows::Forms::Label();
			this->P2Title = new System::Windows::Forms::Label();
			this->P1Title = new System::Windows::Forms::Label();
			this->SuspendLayout();
			// 
			// GameLoop
			// 
			this->GameLoop->Interval = 40;
			this->GameLoop->Tick += new System::EventHandler(this, GameLoop_Tick);
			// 
			// TankImage
			// 
			this->TankImage->ImageSize = System::Drawing::Size(31, 35);
			this->TankImage->ImageStream = (__try_cast<System::Windows::Forms::ImageListStreamer *  >(resources->GetObject(S"TankImage.ImageStream")));
			this->TankImage->TransparentColor = System::Drawing::Color::White;
			// 
			// TurretImage
			// 
			this->TurretImage->ImageSize = System::Drawing::Size(4, 26);
			this->TurretImage->ImageStream = (__try_cast<System::Windows::Forms::ImageListStreamer *  >(resources->GetObject(S"TurretImage.ImageStream")));
			this->TurretImage->TransparentColor = System::Drawing::Color::White;
			// 
			// Start1P
			// 
			this->Start1P->BackColor = System::Drawing::Color::LimeGreen;
			this->Start1P->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Start1P->Location = System::Drawing::Point(360, 256);
			this->Start1P->Name = S"Start1P";
			this->Start1P->TabIndex = 2;
			this->Start1P->Text = S"Start game (1P)";
			this->Start1P->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Start1P->Click += new System::EventHandler(this, Start1P_Click);
			this->Start1P->MouseEnter += new System::EventHandler(this, Control_MouseEnter);
			this->Start1P->MouseLeave += new System::EventHandler(this, Control_MouseLeave);
			// 
			// Start2P
			// 
			this->Start2P->BackColor = System::Drawing::Color::ForestGreen;
			this->Start2P->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Start2P->Location = System::Drawing::Point(464, 256);
			this->Start2P->Name = S"Start2P";
			this->Start2P->TabIndex = 3;
			this->Start2P->Text = S"Start game (2P)";
			this->Start2P->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Start2P->Click += new System::EventHandler(this, Start2P_Click);
			this->Start2P->MouseEnter += new System::EventHandler(this, Control_MouseEnter);
			this->Start2P->MouseLeave += new System::EventHandler(this, Control_MouseLeave);
			// 
			// VictoryLabel
			// 
			this->VictoryLabel->BackColor = System::Drawing::Color::PaleGreen;
			this->VictoryLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->VictoryLabel->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->VictoryLabel->ForeColor = System::Drawing::Color::Red;
			this->VictoryLabel->Location = System::Drawing::Point(368, 288);
			this->VictoryLabel->Name = S"VictoryLabel";
			this->VictoryLabel->Size = System::Drawing::Size(184, 24);
			this->VictoryLabel->TabIndex = 4;
			this->VictoryLabel->Text = S"PLAYER X WINS";
			this->VictoryLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->VictoryLabel->Visible = false;
			// 
			// VictorySFX
			// 
			this->VictorySFX->Interval = 40;
			// 
			// Settings
			// 
			this->Settings->BackColor = System::Drawing::Color::OliveDrab;
			this->Settings->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Settings->Location = System::Drawing::Point(464, 320);
			this->Settings->Name = S"Settings";
			this->Settings->TabIndex = 5;
			this->Settings->Text = S"Settings";
			this->Settings->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Settings->Click += new System::EventHandler(this, Settings_Click);
			this->Settings->MouseEnter += new System::EventHandler(this, Control_MouseEnter);
			this->Settings->MouseLeave += new System::EventHandler(this, Control_MouseLeave);
			// 
			// Simulate
			// 
			this->Simulate->BackColor = System::Drawing::Color::DarkGreen;
			this->Simulate->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Simulate->Location = System::Drawing::Point(360, 320);
			this->Simulate->Name = S"Simulate";
			this->Simulate->TabIndex = 6;
			this->Simulate->Text = S"Custom game";
			this->Simulate->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Simulate->Click += new System::EventHandler(this, Simulate_Click);
			this->Simulate->MouseEnter += new System::EventHandler(this, Control_MouseEnter);
			this->Simulate->MouseLeave += new System::EventHandler(this, Control_MouseLeave);
			// 
			// FastLoop
			// 
			this->FastLoop->Interval = 24;
			this->FastLoop->Tick += new System::EventHandler(this, FastLoop_Tick);
			// 
			// EditorLoop
			// 
			this->EditorLoop->Interval = 25;
			this->EditorLoop->Tick += new System::EventHandler(this, EditorLoop_Tick);
			// 
			// P2Label
			// 
			this->P2Label->BackColor = System::Drawing::Color::LightGreen;
			this->P2Label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P2Label->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P2Label->ForeColor = System::Drawing::Color::OrangeRed;
			this->P2Label->Location = System::Drawing::Point(760, 40);
			this->P2Label->Name = S"P2Label";
			this->P2Label->Size = System::Drawing::Size(88, 72);
			this->P2Label->TabIndex = 7;
			this->P2Label->Text = S"2";
			this->P2Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->P2Label->MouseDown += new System::Windows::Forms::MouseEventHandler(this, P2Label_MouseDown);
			// 
			// P1Label
			// 
			this->P1Label->BackColor = System::Drawing::Color::LightGreen;
			this->P1Label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P1Label->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P1Label->ForeColor = System::Drawing::Color::DodgerBlue;
			this->P1Label->Location = System::Drawing::Point(64, 472);
			this->P1Label->Name = S"P1Label";
			this->P1Label->Size = System::Drawing::Size(88, 72);
			this->P1Label->TabIndex = 8;
			this->P1Label->Text = S"1";
			this->P1Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->P1Label->MouseDown += new System::Windows::Forms::MouseEventHandler(this, P1Label_MouseDown);
			// 
			// P4Label
			// 
			this->P4Label->BackColor = System::Drawing::Color::LightGreen;
			this->P4Label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P4Label->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P4Label->ForeColor = System::Drawing::Color::Yellow;
			this->P4Label->Location = System::Drawing::Point(752, 472);
			this->P4Label->Name = S"P4Label";
			this->P4Label->Size = System::Drawing::Size(88, 72);
			this->P4Label->TabIndex = 9;
			this->P4Label->Text = S"4";
			this->P4Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->P4Label->MouseDown += new System::Windows::Forms::MouseEventHandler(this, P4Label_MouseDown);
			// 
			// P3Label
			// 
			this->P3Label->BackColor = System::Drawing::Color::LightGreen;
			this->P3Label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P3Label->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P3Label->ForeColor = System::Drawing::Color::Lime;
			this->P3Label->Location = System::Drawing::Point(64, 40);
			this->P3Label->Name = S"P3Label";
			this->P3Label->Size = System::Drawing::Size(88, 72);
			this->P3Label->TabIndex = 10;
			this->P3Label->Text = S"3";
			this->P3Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->P3Label->MouseDown += new System::Windows::Forms::MouseEventHandler(this, P3Label_MouseDown);
			// 
			// P3Title
			// 
			this->P3Title->BackColor = System::Drawing::Color::PaleGreen;
			this->P3Title->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P3Title->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P3Title->ForeColor = System::Drawing::Color::Black;
			this->P3Title->Location = System::Drawing::Point(64, 112);
			this->P3Title->Name = S"P3Title";
			this->P3Title->Size = System::Drawing::Size(88, 24);
			this->P3Title->TabIndex = 15;
			this->P3Title->Text = S"AI 3";
			this->P3Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// P4Title
			// 
			this->P4Title->BackColor = System::Drawing::Color::PaleGreen;
			this->P4Title->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P4Title->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P4Title->ForeColor = System::Drawing::Color::Black;
			this->P4Title->Location = System::Drawing::Point(752, 544);
			this->P4Title->Name = S"P4Title";
			this->P4Title->Size = System::Drawing::Size(88, 24);
			this->P4Title->TabIndex = 17;
			this->P4Title->Text = S"AI 4";
			this->P4Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// P2Title
			// 
			this->P2Title->BackColor = System::Drawing::Color::PaleGreen;
			this->P2Title->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P2Title->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P2Title->ForeColor = System::Drawing::Color::Black;
			this->P2Title->Location = System::Drawing::Point(760, 112);
			this->P2Title->Name = S"P2Title";
			this->P2Title->Size = System::Drawing::Size(88, 24);
			this->P2Title->TabIndex = 18;
			this->P2Title->Text = S"Human/AI 2";
			this->P2Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// P1Title
			// 
			this->P1Title->BackColor = System::Drawing::Color::PaleGreen;
			this->P1Title->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->P1Title->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->P1Title->ForeColor = System::Drawing::Color::Black;
			this->P1Title->Location = System::Drawing::Point(64, 544);
			this->P1Title->Name = S"P1Title";
			this->P1Title->Size = System::Drawing::Size(88, 24);
			this->P1Title->TabIndex = 19;
			this->P1Title->Text = S"Human 1";
			this->P1Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->BackColor = System::Drawing::Color::LightGreen;
			this->ClientSize = System::Drawing::Size(912, 600);
			this->Controls->Add(this->P1Title);
			this->Controls->Add(this->P2Title);
			this->Controls->Add(this->P4Title);
			this->Controls->Add(this->P3Title);
			this->Controls->Add(this->P3Label);
			this->Controls->Add(this->P4Label);
			this->Controls->Add(this->P1Label);
			this->Controls->Add(this->P2Label);
			this->Controls->Add(this->Simulate);
			this->Controls->Add(this->Settings);
			this->Controls->Add(this->VictoryLabel);
			this->Controls->Add(this->Start2P);
			this->Controls->Add(this->Start1P);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(480, 390);
			this->Name = S"Form1";
			this->Text = S"LaserTanks";
			this->KeyDown += new System::Windows::Forms::KeyEventHandler(this, Form1_KeyDown);
			this->Resize += new System::EventHandler(this, Form1_Resize);
			this->MouseDown += new System::Windows::Forms::MouseEventHandler(this, Form1_MouseDown);
			this->KeyUp += new System::Windows::Forms::KeyEventHandler(this, Form1_KeyUp);
			this->MouseMove += new System::Windows::Forms::MouseEventHandler(this, Form1_MouseMove);
			this->ResumeLayout(false);

		}	
	private: double rad(int theta) // Converts degrees to radians (degrees suck but are simple)
			 {
				 return theta * Math::PI / 180;
			 }
	private: int deg(double theta) // Converts radians to degrees (radians are great but complicated)
			 {
				 return (int)(theta / Math::PI * 180);
			 }
	private: int CheckCollision(float _x, float _y, int source)
			 {
				 if (_x < 0 || _x > this->Width || _y < 0 || _y > this->Height)
					 return -2; // Off-screen
				 for (int i = 0; i < tMax; i++)
				 {
					 if (i == source || !exists[i]) // Err... yeah. Should be pretty self-explanatory
						 continue;
					 if (_x > x[i]-sx/2 && _x < x[i]+sx/2 && _y > y[i]-sy/2 && _y < y[i]+sy/2)
						 return i; // Return index of unfortunate victim
				 }
				 return -1; // No collision
			 }
	private: void CheckBoundaries(int t)
			 {
				 // Check map boundaries
				 if (x[t] < xl || x[t] > xr)
				 {
					 x[t] -= dx[t]; // Negate change
					 dx[t] = 0;
				 }
				 if (y[t] < yt || y[t] > yb)
				 {
					 y[t] -= dy[t];
					 dy[t] = 0;
				 }
				 // Check collisions with other tanks
				 for (int i = 0; i < tMax; i++)
				 {
					 if (i == t || !exists[i]) // Look familiar?
						 continue;
					 if (x[t]+sx > x[i] && x[t]-sx < x[i] && y[t]+sy > y[i] && y[t]-sy < y[i])
					 {
						 x[t] -= dx[t];
						 y[t] -= dy[t];
						 dx[t] = 0;
						 dy[t] = 0;
						 break;
					 }
				 }
			 }
	private: bool CheckBoundaries(int t, int _tmax)
			 {
				 // Check map boundaries
				 if (x[t] < xl || x[t] > xr || y[t] < yt || y[t] > yb)
					 return true;
				 // Check collisions with other tanks
				 for (int i = 0; i < _tmax; i++)
				 {
					 if (i == t || !exists[i]) // Look familiar?
						 continue;
					 if (x[t]+sx > x[i] && x[t]-sx < x[i] && y[t]+sy > y[i] && y[t]-sy < y[i])
						 return true;
				 }
				 return false;
			 }
	private: void ReduceHealth(int ti, int dh)
			 {
				 if (hp[ti] <= 0 || GameEnding != -1) // Health can't really get any lower by that stage anyway...
					 return; // But seriously, it prevents the death animation resetting.
				 hs[ti] = ht;
				 hp[ti] -= dh;
				 int lc __gc[] = new int __gc[tMax];
				 int slc = 0;
				 at = -1;
				 if (hp[ti] <= 0)
				 {
					 recoil[ti] = 500;
					 sd[ti] = 32767;
					 for (int i = 0; i < tMax; i++)
					 {
						 if (exists[i] && recoil[i] < 200)
						 {
							 lc[team[i]]++;
							 at = team[i];
						 }
					 }
					 for (int i = 0; i < tMax; i++)
					 {
						 if (lc[i] > 0)
							 slc++;
					 }
					 if (slc <= 1)
						 GameEnding = ti;
				 }
			 }
	private: bool AICore(int i)
			{
				int mt, theta, ta;
				double rx, ry;
				if (recoil[i] != 0)
					return 1;
				// Randomly change stance. Stance affects movement but not turret controls
				if (d_stance[i])
				{
					if (r->Next(0,100) == 0)
						stance[i] = r->Next(0,1);
				}
				// Resolve technical targeting issues by all means necessary...
				bool cft = false;
				for (int j = 0; j < tMax; j++)
				{
					if (j == i || !exists[j] || team[j] == team[i] || recoil[j] > 200)
						continue;
					else
					{
						cft = true;
						break;
					}
				}
				if (cft = false)
				{
					dx[i] = 0;
					dy[i] = 0;
					dd[i] = 0;
					return 0;
				}
				int ii = 0; 
				while (tgt[i] == i || !exists[tgt[i]] || team[tgt[i]] == team[i] || recoil[tgt[i]] > 300)
				{
					tgt[i] = r->Next(0, tMax);
					ii++;
					if (ii > 200)
						break;
				}
				if (sd[i] == 0) // With this check, fire rate will be slower if target is moving
				{
					// Get relative location and angle of target, and calculate aiming angle
					rx = x[tgt[i]] - x[i];
					ry = y[tgt[i]] - y[i];
					if (ry > 0)  // Note that ry cannot be zero, as this would cause division by 0
						theta = 180 + deg(Math::Atan(rx/-ry));
					else if (ry < 0 && rx < 0)
						theta = 360 + deg(Math::Atan(rx/-ry));
					else if (ry < 0 && rx >= 0)
						theta = deg(Math::Atan(rx/-ry));
					else if (rx < 0)
						theta = 270;
					else
						theta = 90;
					ta = theta + disp[i] - td[i];
					// Aim turret towards target (with dispersion)
					if (ta > 180 || (ta < -2 && ta > -180))
						dd[i] = -1;
					else if (ta <= -180 || (ta > 2 && ta <= 180))
						dd[i] = 1;
					else
						dd[i] = 0;
				}
				// If turret is pointing at target spot, fire a laser
				if (dd[i] == 0 && sd[i] == 0)
				{
					// Implement multiple-shot constraints
					recoil[i] = 5;
					ammo[i]--;
					if (ammo[i] == 0)
					{
						ammo[i] = crs;
						sd[i] = -rlt;
					}
					else
						sd[i] = sdi;
					int p = 0;
					for (p = 0; p < pMax; p++)
					{
						if (px1[p] == -32)
							break;
					}
					// Fire at the target spot!
					px1[p] = (float)x[i] + 10*Math::Sin(rad(td[i]));
					py1[p] = (float)y[i] - 5 - 10*Math::Cos(rad(td[i]));
					px2[p] = px1[p];
					py2[p] = py1[p];
					int cc;
					for (;;)
					{
						px2[p] += 2*Math::Sin(rad(td[i]));
						py2[p] -= 2*Math::Cos(rad(td[i]));
						cc = CheckCollision(px2[p], py2[p], i);
						if (cc != -1)
							break;
					}
					if (cc >= 0 && team[cc] != team[i])
						ReduceHealth(cc, 1);
					else if (cc >= 0 && team[cc] == team[i])
					{
						if (ffs == 1)
							ReduceHealth(cc, 1);
						else if (ffs == 2)
							ReduceHealth(i, 1);
					}
					pro_s[p] = 5;
					pd[p] = td[i];
					if (d_tgt[i])
					{
						// Randomize dispersion on next shot
						disp[i] = r->Next(-dmax[i], dmax[i]+1);
						// Switch targets once in a while
						if (r->Next(0,4) == 0)
						{
							mt = tgt[i];
							tgt[i] = r->Next(0, tMax);
							if (tgt[i] == i || !exists[i] || team[tgt[i]] == team[i] || recoil[i] > 300)
								tgt[i] = mt;
						}
					}
				}
				// Control tank movement
				switch (stance[i])
				{
				case 0: // Random movement
					switch (r->Next(0,(int)24/dcr))
					{
					case 0:
						dx[i] = 0;
						dy[i] = 0;
						break;
					case 1:
						dx[i] = sp;
						dy[i] = 0;
						break;
					case 2:
						dx[i] = -sp;
						dy[i] = 0;
						break;
					case 3:
						dx[i] = 0;
						dy[i] = sp;
						break;
					case 4:
						dx[i] = 0;
						dy[i] = -sp;
						break;
					case 5:
						dx[i] = dsp;
						dy[i] = dsp;
						break;
					case 6:
						dx[i] = dsp;
						dy[i] = -dsp;
						break;
					case 7:
						dx[i] = -dsp;
						dy[i] = dsp;
						break;
					case 8:
						dx[i] = -dsp;
						dy[i] = -dsp;
						break;
					}
					break;
					// TODO: Other stances, if needed!
				}
				return 1;
			}
	private: void InitializeGame(bool start)
			 {
				 this->MinimumSize = this->Size;
				 this->MaximumSize = this->Size;
				 this->MaximizeBox = false;
				 GameLoop->Enabled = start;
				 FastLoop->Enabled = start;
				 Start1P->Visible = false;
				 Start2P->Visible = false;
				 Settings->Visible = false;
				 Simulate->Visible = false;
				 VictorySFX->Enabled = false;
				 VictoryLabel->Visible = false;
				 P1Label->Visible = false;
				 P2Label->Visible = false;
				 P3Label->Visible = false;
				 P4Label->Visible = false;
				 P1Title->Visible = false;
				 P2Title->Visible = false;
				 P3Title->Visible = false;
				 P4Title->Visible = false;
				 this->Cursor = Cursors::Default;
				 if (!start)
				 {
					 for (int i = 0; i < TMAX; i++)
						 exists[i] = false;
					 EditMode = false;
					 EditorLoop->Enabled = false;
				 }
				 else
				 {
					 team[0] = Convert::ToInt32(P1Label->Text); team[0]--;
					 team[1] = Convert::ToInt32(P2Label->Text); team[1]--;
					 team[2] = Convert::ToInt32(P3Label->Text); team[2]--;
					 team[3] = Convert::ToInt32(P4Label->Text); team[3]--;
				 }
			 }
	private: void EndGame(int vi)
			 {
				 GameLoop->Enabled = false;
				 FastLoop->Enabled = false;
				 EditMode = false;
				 EditorLoop->Enabled = false;
				 this->MinimumSize = Drawing::Size(400,240);
				 this->MaximumSize = Drawing::Size(0,0);
				 this->MaximizeBox = true;
				 vi++;
				 bool teams = false;
				 for (int i = 0; i < tMax; i++)
				 {
					 for (int j = 0; j < tMax; j++)
					 {
						 if (i == j)
							 continue;
						 else if (team[i] == team[j])
						 {
							 teams = true;
							 break;
						 }
					 }
					 if (teams)
						 break;
				 }
				 if (vi != 0 && !teams && !ai[vi])
					 VictoryLabel->Text = String::Concat("PLAYER ", vi.ToString(), " WINS");
				 else if (vi != 0 && !teams && ai[vi])
					 VictoryLabel->Text = String::Concat("AI ", vi.ToString(), " WINS");
				 else if (vi != 0 && teams)
					 VictoryLabel->Text = String::Concat("TEAM ", vi.ToString(), " WINS");
				 else
					 VictoryLabel->Text = "NOBODY WINS";
				 VictoryLabel->Visible = true;
				 Start1P->Visible = true;
				 Start2P->Visible = true;
				 Settings->Visible = true;
				 Simulate->Visible = true;
				 P1Label->Visible = true;
				 P2Label->Visible = true;
				 P3Label->Visible = true;
				 P4Label->Visible = true;
				 P1Title->Visible = true;
				 P2Title->Visible = true;
				 P3Title->Visible = true;
				 P4Title->Visible = true;
				 this->Cursor = Cursors::Default;
				 GameEnding = -1;
			 }
	private: void EndGame(void)
			 {
				 GameLoop->Enabled = false;
				 FastLoop->Enabled = false;
				 EditMode = false;
				 EditorLoop->Enabled = false;
				 this->MinimumSize = Drawing::Size(280,240);
				 this->MaximumSize = Drawing::Size(0,0);
				 this->MaximizeBox = true;
				 Start1P->Visible = true;
				 Start2P->Visible = true;
				 Settings->Visible = true;
				 Simulate->Visible = true;
				 P1Label->Visible = true;
				 P2Label->Visible = true;
				 P3Label->Visible = true;
				 P4Label->Visible = true;
				 P1Title->Visible = true;
				 P2Title->Visible = true;
				 P3Title->Visible = true;
				 P4Title->Visible = true;
				 this->Cursor = Cursors::Default;
				 GameEnding = -1;
			 }
	private: System::Void Start1P_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 if (PauseState)
				 {
					 PauseState = false;
					 GameLoop->Enabled = true;
					 FastLoop->Enabled = true;
					 Start1P->Text = "Start Game (1P)";
					 Start2P->Text = "Start Game (2P)";
					 Start1P->Visible = false;
					 Start2P->Visible = false;
					 return;
				 }
				 Random * r = new Random();
				 for (int i = 0; i < TMAX; i++)
					 exists[i] = false;
				 tMax = 4;
				 pMax = 8;
				 spawn_x[0] = 55 - sx/2;
				 spawn_y[0] = this->Height - 55 - sy/2;
				 init_d[0] = 210;
				 spawn_x[1] = this->Width - 55 - sx/2;
				 spawn_y[1] = 65 - sy/2;
				 init_d[1] = 30;
				 spawn_x[2] = 55 - sx/2;
				 spawn_y[2] = 65 - sy/2;
				 init_d[2] = 330;
				 spawn_x[3] = this->Width - 55 - sx/2;
				 spawn_y[3] = this->Height - 55 - sy/2;
				 init_d[3] = 150;
				 x[0] = spawn_x[0];
				 y[0] = spawn_y[0];
				 hp[0] = hpi;
				 exists[0] = true;
				 ammo[0] = crs;
				 sd[0] = 0;
				 td[0] = init_d[0];
				 dx[0] = 0;
				 dy[0] = 0;
				 dd[0] = 0;
				 team[0] = 0;
				 ai[0] = false;
				 recoil[0] = false;
				 for (int i = 1; i < tMax; i++)
				 {
					 hp[i] = hpi * hpr;
					 exists[i] = true;
					 x[i] = spawn_x[i];
					 y[i] = spawn_y[i];
					 ammo[i] = crs;
					 sd[i] = 0;
					 td[i] = init_d[i];
					 dx[i] = 0;
					 dy[i] = 0;
					 dd[i] = 0;
					 team[i] = i;
					 ai[i] = true;
					 stance[i] = 0;
					 d_stance[i] = true;
					 tgt[i] = i;
					 while (tgt[i] == i)
						 tgt[i] = r->Next(0,4);
					 d_tgt[i] = true;
					 dmax[i] = d_max;
					 disp[i] = r->Next(0, dmax[i]);
					 recoil[i] = false;
				 }
				 InitializeGame(true);
			 }

	private: System::Void Start2P_Click(System::Object *  sender, System::EventArgs *  e)
			{
				 if (PauseState)
				 {
					 PauseState = false;
					 GameLoop->Enabled = false;
					 FastLoop->Enabled = false;
					 Start1P->Text = "Start Game (1P)";
					 Start2P->Text = "Start Game (2P)";
					 EndGame();
					 return;
				 }
				 for (int i = 0; i < TMAX; i++)
					 exists[i] = false;
				 tMax = 4;
				 pMax = 8;
				 spawn_x[0] = 55 - sx/2;
				 spawn_y[0] = this->Height - 55 - sy/2;
				 init_d[0] = 210;
				 spawn_x[1] = this->Width - 55 - sx/2;
				 spawn_y[1] = 65 - sy/2;
				 init_d[1] = 30;
				 spawn_x[2] = 55 - sx/2;
				 spawn_y[2] = 65 - sy/2;
				 init_d[2] = 330;
				 spawn_x[3] = this->Width - 55 - sx/2;
				 spawn_y[3] = this->Height - 55 - sy/2;
				 init_d[3] = 150;
				 // Keep everything below this point sorted by tank ID [], not other variables!
				 hp[0] = hpi;
				 exists[0] = true;
				 x[0] = spawn_x[0];
				 y[0] = spawn_y[0];
				 ammo[0] = crs;
				 sd[0] = 0;
				 td[0] = 210;
				 dx[0] = 0;
				 dy[0] = 0;
				 dd[0] = 0;
				 team[0] = 0;
				 ai[0] = false;
				 recoil[0] = false;
				 hp[1] = hpi;
				 exists[1] = true;
				 x[1] = spawn_x[1];
				 y[1] = spawn_y[1];
				 ammo[1] = crs;
				 sd[1] = 0;
				 td[1] = 30;
				 dx[1] = 0;
				 dy[1] = 0;
				 dd[1] = 0;
				 team[1] = 1;
				 ai[1] = false;
				 recoil[1] = false;
				 for (int i = 2; i < tMax; i++)
				 {
					 hp[i] = hpi * hpr;
					 exists[i] = true;
					 x[i] = spawn_x[i];
					 y[i] = spawn_y[i];
					 ammo[i] = crs;
					 sd[i] = 0;
					 td[i] = init_d[i];
					 dx[i] = 0;
					 dy[i] = 0;
					 dd[i] = 0;
					 team[i] = i;
					 ai[i] = true;
					 stance[i] = 0;
					 d_stance[i] = true;
					 tgt[i] = i;
					 while (tgt[i] == i)
						 tgt[i] = r->Next(0,4);
					 d_tgt[i] = true;
					 dmax[i] = d_max;
					 disp[i] = r->Next(0, dmax[i]);
					 recoil[i] = false;
				 }
				 InitializeGame(true);
			}

	private: System::Void Form1_KeyDown(System::Object *  sender, System::Windows::Forms::KeyEventArgs *  e)
			{
				if (GameLoop->Enabled)
				{
					if (e->KeyValue == U1) 
					{
						if (!exists[0] || ai[0])
							return;
						if (dy[0] == dsp)
							dy[0] = -dsp;
						else if (dy[0] > 0)
						{
							dy[0] = -sp;
							dx[0] = 0;
						}
						else if (dy[0] == -dsp)
						{
							dy[0] = -sp;
							dx[0] = 0;
						}
						else if (dx[0] == 0)
							dy[0] = -sp;
						else if (dx[0] == sp)
						{
							dx[0] = dsp;
							dy[0] = -dsp;
						}
						else if (dx[0] == -sp)
						{
							dx[0] = -dsp;
							dy[0] = -dsp;
						}
						else
							dy[0] = -dsp;
						return;
					}
					else if (e->KeyValue == L1) 
					{
						if (!exists[0] || ai[0])
							return;
						if (dx[0] == dsp)
							dx[0] = -dsp;
						else if (dx[0] > 0)
						{
							dx[0] = -sp;
							dy[0] = 0;
						}
						else if (dx[0] == -dsp)
						{
							dx[0] = -sp;
							dy[0] = 0;
						}
						else if (dy[0] == 0)
							dx[0] = -sp;
						else if (dy[0] == sp)
						{
							dy[0] = dsp;
							dx[0] = -dsp;
						}
						else if (dy[0] == -sp)
						{
							dy[0] = -dsp;
							dx[0] = -dsp;
						}
						else
							dx[0] = -dsp;
						return;
					}
					else if (e->KeyValue == R1) 
					{
						if (!exists[0] || ai[0])
							return;
						if (dx[0] == -dsp)
							dx[0] = dsp;
						else if (dx[0] < 0)
						{
							dx[0] = sp;
							dy[0] = 0;
						}
						else if (dx[0] == dsp)
						{
							dx[0] = sp;
							dy[0] = 0;
						}
						else if (dy[0] == 0)
							dx[0] = sp;
						else if (dy[0] == sp)
						{
							dy[0] = dsp;
							dx[0] = dsp;
						}
						else if (dy[0] == -sp)
						{
							dy[0] = -dsp;
							dx[0] = dsp;
						}
						else
							dx[0] = dsp;
						return;
					}
					else if (e->KeyValue == D1) 
					{
						if (!exists[0] || ai[0])
							return;
						if (dy[0] == -dsp)
							dy[0] = dsp;
						else if (dy[0] < 0)
						{
							dy[0] = sp;
							dx[0] = 0;
						}
						else if (dy[0] == dsp)
						{
							dy[0] = sp;
							dx[0] = 0;
						}
						else if (dx[0] == 0)
							dy[0] = sp;
						else if (dx[0] == sp)
						{
							dx[0] = dsp;
							dy[0] = dsp;
						}
						else if (dx[0] == -sp)
						{
							dx[0] = -dsp;
							dy[0] = dsp;
						}
						else
							dy[0] = dsp;
						return;
					}
					else if (e->KeyValue == U2) 
					{
						if (!exists[1] || ai[1])
							return;
						if (dy[1] == dsp)
							dy[1] = -dsp;
						else if (dy[1] > 0)
						{
							dy[1] = -sp;
							dx[1] = 0;
						}
						else if (dy[1] == -dsp)
						{
							dy[1] = -sp;
							dx[1] = 0;
						}
						else if (dx[1] == 0)
							dy[1] = -sp;
						else if (dx[1] == sp)
						{
							dx[1] = dsp;
							dy[1] = -dsp;
						}
						else if (dx[1] == -sp)
						{
							dx[1] = -dsp;
							dy[1] = -dsp;
						}
						else
							dy[1] = -dsp;
						return;
					}
					else if (e->KeyValue == L2) 
					{
						if (!exists[1] || ai[1])
							return;
						if (dx[1] == dsp)
							dx[1] = -dsp;
						else if (dx[1] > 0)
						{
							dx[1] = -sp;
							dy[1] = 0;
						}
						else if (dx[1] == -dsp)
						{
							dx[1] = -sp;
							dy[1] = 0;
						}
						else if (dy[1] == 0)
							dx[1] = -sp;
						else if (dy[1] == sp)
						{
							dy[1] = dsp;
							dx[1] = -dsp;
						}
						else if (dy[1] == -sp)
						{
							dy[1] = -dsp;
							dx[1] = -dsp;
						}
						else
							dx[1] = -dsp;
						return;
					}
					else if (e->KeyValue == R2) 
					{
						if (!exists[1] || ai[1])
							return;
						if (dx[1] == -dsp)
							dx[1] = dsp;
						else if (dx[1] < 0)
						{
							dx[1] = sp;
							dy[1] = 0;
						}
						else if (dx[1] == dsp)
						{
							dx[1] = sp;
							dy[1] = 0;
						}
						else if (dy[1] == 0)
							dx[1] = sp;
						else if (dy[1] == sp)
						{
							dy[1] = dsp;
							dx[1] = dsp;
						}
						else if (dy[1] == -sp)
						{
							dy[1] = -dsp;
							dx[1] = dsp;
						}
						else
							dx[1] = dsp;
						return;
					}
					else if (e->KeyValue == D2) 
					{
						if (!exists[1] || ai[1])
							return;
						if (dy[1] == -dsp)
							dy[1] = dsp;
						else if (dy[1] < 0)
						{
							dy[1] = sp;
							dx[1] = 0;
						}
						else if (dy[1] == dsp)
						{
							dy[1] = sp;
							dx[1] = 0;
						}
						else if (dx[1] == 0)
							dy[1] = sp;
						else if (dx[1] == sp)
						{
							dx[1] = dsp;
							dy[1] = dsp;
						}
						else if (dx[1] == -sp)
						{
							dx[1] = -dsp;
							dy[1] = dsp;
						}
						else
							dy[1] = dsp;
						return;
					}
					else if (e->KeyValue == ST1)
					{
						if (!exists[0] || ai[0])
							return;
						dx[0] = 0;
						dy[0] = 0;
					}
					else if (e->KeyValue == ST2)
					{
						if (!exists[1] || ai[1])
							return;
						dx[1] = 0;
						dy[1] = 0;
					}
					else if (e->KeyValue == RC1 && recoil[0] < 200) 
					{
						if (!exists[0] || ai[0])
							return;
						dd[0] = 1;
					}
					else if (e->KeyValue == RA1 && recoil[0] < 200) 
					{
						if (!exists[0] || ai[0])
							return;
						dd[0] = -1;
					}
					else if (e->KeyValue == RC2 && recoil[1] < 200) 
					{
						if (!exists[1] || ai[1])
							return;
						dd[1] = 1;
					}
					else if (e->KeyValue == RA2 && recoil[1] < 200) 
					{
						if (!exists[1] || ai[1])
							return;
						dd[1] = -1;
					}
					else if (e->KeyValue == P1 || e->KeyValue == P2)
					{
						PauseState = true;
						GameLoop->Enabled = false;
						FastLoop->Enabled = false;
						Start1P->Text = "Resume";
						Start2P->Text = "Quit Game";
						Start1P->Visible = true;
						Start2P->Visible = true;
					}
					else if (e->KeyValue == S1)
					{
						if (!exists[0] || ai[0])
							return;
						if (sd[0] != 0) // Shot delay could be positive or negative
							return;
						// Implement multiple-shot constraints
						recoil[0] = 5;
						ammo[0]--;
						if (ammo[0] == 0)
						{
							ammo[0] = crs;
							sd[0] = -rlt; // Shot delay = Reload time (negated)
						}
						else
							sd[0] = sdi; // Shot delay = Standard shot delay
						int p = 0;
						for (p = 0; p < pMax; p++)
						{
							if (px1[p] == -32)
								break;
						}
						px1[p] = (float)x[0] + 10*Math::Sin(rad(td[0]));
						py1[p] = (float)y[0] - 5 - 10*Math::Cos(rad(td[0]));
						px2[p] = px1[p];
						py2[p] = py1[p];
						int cc;
						for (;;)
						{
							px2[p] += 2*Math::Sin(rad(td[0]));
							py2[p] -= 2*Math::Cos(rad(td[0]));
							cc = CheckCollision(px2[p], py2[p], 0);
							if (cc != -1)
								break;
						}
						if (cc >= 0 && team[cc] != team[0])
							ReduceHealth(cc, 1);
						else if (cc >= 0 && team[cc] == team[0])
						{
							if (ffs == 1)
								ReduceHealth(cc, 1);
							else if (ffs == 2)
								ReduceHealth(0, 1);
						}
						pro_s[p] = 5;
						pd[p] = td[0];
					}
					else if (e->KeyValue == S2)
					{
						if (!exists[1] || ai[1])
							return;
						if (sd[1] != 0) // Shot delay could be positive or negative
							return;
						// Implement multiple-shot constraints
						recoil[1] = 5;
						ammo[1]--;
						if (ammo[1] == 0)
						{
							ammo[1] = crs;
							sd[1] = -rlt; // Shot delay = Reload time (negated)
						}
						else
							sd[1] = sdi; // Shot delay = Standard shot delay
						int p = 0;
						for (p = 0; p < pMax; p++)
						{
							if (px1[p] == -32)
								break;
						}
						px1[p] = (float)x[1] + 10*Math::Sin(rad(td[1]));
						py1[p] = (float)y[1] - 5 - 10*Math::Cos(rad(td[1]));
						px2[p] = px1[p];
						py2[p] = py1[p];
						int cc;
						for (;;)
						{
							px2[p] += 2*Math::Sin(rad(td[1]));
							py2[p] -= 2*Math::Cos(rad(td[1]));
							cc = CheckCollision(px2[p], py2[p], 1);
							if (cc != -1)
								break;
						}
						if (cc >= 0 && team[cc] != team[1])
							ReduceHealth(cc, 1);
						else if (cc >= 0 && team[cc] == team[1])
						{
							if (ffs == 1)
								ReduceHealth(cc, 1);
							else if (ffs == 2)
								ReduceHealth(1, 1);
						}
						pro_s[p] = 5;
						pd[p] = td[1];
					}
				}
				else if (EditMode)
				{
					if (e->KeyValue == Forms::Keys::Escape)
						EndGame();
					else if (e->KeyValue == Forms::Keys::Enter)
					{
						EditMode = false;
						EditorLoop->Enabled = false;
						tMax = ct;
						pMax = tMax*2;
						for (int i = 0; i < tMax; i++)
						{
							hp[i] = hpi * hpr;
							exists[i] = true;
							ammo[i] = crs;
							sd[i] = 0;
							dx[i] = 0;
							dy[i] = 0;
							dd[i] = 0;
							team[i] = i;
							ai[i] = true;
							stance[i] = 0;
							d_stance[i] = true;
							tgt[i] = i;
							while (tgt[i] == i)
								tgt[i] = r->Next(0,tMax);
							d_tgt[i] = true;
							dmax[i] = d_max;
							disp[i] = r->Next(0, dmax[i]);
							recoil[i] = false;	
						}
						P1Label->Text = "1";
						P2Label->Text = "2";
						P3Label->Text = "3";
						P4Label->Text = "4";
						InitializeGame(true);
					}
					else if (e->KeyValue == Forms::Keys::D1)
					{
						EditMode = false;
						EditorLoop->Enabled = false;
						tMax = ct;
						pMax = tMax*2;
						hp[0] = hpi;
						exists[0] = true;
						ammo[0] = crs;
						sd[0] = 0;
						dx[0] = 0;
						dy[0] = 0;
						dd[0] = 0;
						team[0] = 0;
						ai[0] = false;
						recoil[0] = false;
						for (int i = 1; i < tMax; i++)
						{
							hp[i] = hpi * hpr;
							exists[i] = true;
							ammo[i] = crs;
							sd[i] = 0;
							dx[i] = 0;
							dy[i] = 0;
							dd[i] = 0;
							team[i] = i;
							ai[i] = true;
							stance[i] = 0;
							d_stance[i] = true;
							tgt[i] = i;
							while (tgt[i] == i)
								tgt[i] = r->Next(0,tMax);
							d_tgt[i] = true;
							dmax[i] = d_max;
							disp[i] = r->Next(0, dmax[i]);
							recoil[i] = false;
						}
						P1Label->Text = "1";
						P2Label->Text = "2";
						P3Label->Text = "3";
						P4Label->Text = "4";
						InitializeGame(true);
					}
					else if (e->KeyValue == Forms::Keys::D2)
					{
						EditMode = false;
						EditorLoop->Enabled = false;
						tMax = ct;
						pMax = tMax*2;
						hp[0] = hpi;
						exists[0] = true;
						ammo[0] = crs;
						sd[0] = 0;
						dx[0] = 0;
						dy[0] = 0;
						dd[0] = 0;
						team[0] = 0;
						ai[0] = false;
						recoil[0] = false;
						hp[1] = hpi;
						exists[1] = true;
						ammo[1] = crs;
						sd[1] = 0;
						dx[1] = 0;
						dy[1] = 0;
						dd[1] = 0;
						team[1] = 1;
						ai[1] = false;
						recoil[1] = false;
						for (int i = 2; i < tMax; i++)
						{
							hp[i] = hpi * hpr;
							exists[i] = true;
							ammo[i] = crs;
							sd[i] = 0;
							dx[i] = 0;
							dy[i] = 0;
							dd[i] = 0;
							team[i] = i;
							ai[i] = true;
							stance[i] = 0;
							d_stance[i] = true;
							tgt[i] = i;
							while (tgt[i] == i)
								tgt[i] = r->Next(0,tMax);
							d_tgt[i] = true;
							dmax[i] = d_max;
							disp[i] = r->Next(0, dmax[i]);
							recoil[i] = false;
						}
						P1Label->Text = "1";
						P2Label->Text = "2";
						P3Label->Text = "3";
						P4Label->Text = "4";
						InitializeGame(true);
					}
				}
			}

	private: System::Void Form1_KeyUp(System::Object *  sender, System::Windows::Forms::KeyEventArgs *  e)
			 {
				 if (!GameLoop->Enabled)
					 return;
				 if ((e->KeyValue == RC1 || e->KeyValue == RA1) && recoil[0] < 200)
				 {
					 dd[0] = 0;
				 }
			     else if ((e->KeyValue == RC2 || e->KeyValue == RA2) && recoil[1] < 200)
				 {
					 dd[1] = 0;
				 }
			 }

	private: System::Void GameLoop_Tick(System::Object *  sender, System::EventArgs *  e)
			 {
				 // Bitmap initialized once only in Form1 constructor to prevent memory escalation
				 Graphics * g = Graphics::FromImage(bmp); // Double-buffered to prevent flashing
				 g->Clear(this->BackColor); // TODO: Maybe add an image of sorts? Or not
				 // Tank logic
				 for (int i = 0; i < tMax; i++)
				 {
					 if (!exists[i])
						 continue;
					 // Run the AI core logic (strictly not for humans)
					 bool aic = true;
					 if (ai[i] && GameEnding == -1)
						 aic = AICore(i); // Prevent any damage being done if the AI feels depressed.
					 // If not recoiling, move tank according to current x and y-change values
					 if (recoil[i] == 0 && aic)
					 {
						 x[i] += dx[i];
						 y[i] += dy[i];
					 }
					 else if (aic) // Recoil/deathstate progress
					 {
						 recoil[i]--;
						 if (recoil[i] > 300 && ai[i])
							 dd[i] = 16;
						 else if (recoil[i] > 300)
							 dd[i] = 8;
						 int p = 0;
						 int cc;
						 switch (recoil[i])
						 {
						 case 490:
						 case 467:
						 case 444:
						 case 421:
							 t_img[i] = TankImage->Images->get_Item(1);
							 for (p = 0; p < pMax; p++)
							 {
								 if (px1[p] == -32)
									 break;
							 }
							 px1[p] = (float)x[i] + 10*Math::Sin(rad(td[i]));
							 py1[p] = (float)y[i] - 5 - 10*Math::Cos(rad(td[i]));
							 px2[p] = px1[p];
							 py2[p] = py1[p];
							 for (;;)
							 {
								 px2[p] += 2*Math::Sin(rad(td[i]));
								 py2[p] -= 2*Math::Cos(rad(td[i]));
								 cc = CheckCollision(px2[p], py2[p], i);
								 if (cc != -1)
									 break;
							 }
							 if (cc >= 0)
								 ReduceHealth(cc, 1);
							 pro_s[p] = 5;
							 pd[p] = td[i];
							 break;
						 case 479:
						 case 456:
						 case 433:
						 case 410:
							 t_img[i] = TankImage->Images->get_Item(0);
							 for (p = 0; p < pMax; p++)
							 {
								 if (px1[p] == -32)
									 break;
							 }
							 px1[p] = (float)x[i] + 10*Math::Sin(rad(td[i]));
							 py1[p] = (float)y[i] - 5 - 10*Math::Cos(rad(td[i]));
							 px2[p] = px1[p];
							 py2[p] = py1[p];
							 for (;;)
							 {
								 px2[p] += 2*Math::Sin(rad(td[i]));
								 py2[p] -= 2*Math::Cos(rad(td[i]));
								 cc = CheckCollision(px2[p], py2[p], i);
								 if (cc != -1)
									 break;
							 }
							 if (cc >= 0)
								 ReduceHealth(cc, 1);
							 pro_s[p] = 5;
							 pd[p] = td[i];
							 break;
						 case 385:
							 exists[i] = false;
							 if (GameEnding == i)
							 {
								 EndGame(at);
								 return;
							 }
							 continue;
						 }
					 }
					 if (aic)
					 {
						 // Check tank is not colliding with anything and auto-correct
						 CheckBoundaries(i);
						 // Reduce shot delay (depending on delay type it may be positive or negative)
						 if (sd[i] > 0)
							 sd[i]--;
						 else if (sd[i] < 0)
							 sd[i]++;
					 }
					 // Draw tank, team colour, turret and reload bar
					 g->DrawImageUnscaled(t_img[i], Point((float)x[i]-sx/2, (float)y[i]-sy/2));
					 if (sd[i] > sdi*0.9 || sd[i] < rlt*-0.9)
						 g->FillRectangle(Brushes::Black, x[i]-4, y[i]+14, 9.0, 2.0);
					 else if (sd[i] == 0)
						 g->FillRectangle(Brushes::Lime, x[i]-4, y[i]+14, 9.0, 2.0);
					 else if (sd[i] > 0)
						 g->FillRectangle(Brushes::Lime, x[i]-4, y[i]+14, (8 - 8.9*sd[i]/sdi), 2.0);
					 else
						 g->FillRectangle(Brushes::Lime, x[i]-4, y[i]+14, (8 + 8.9*sd[i]/rlt), 2.0);
					 SolidBrush * br = new SolidBrush(Color::Black);
					 br->Color = cs[team[i]];
					 g->FillRectangle(br, x[i]-12, y[i]-5, 3.0, 6.0);
					 g->FillRectangle(br, x[i]+9, y[i]-5, 3.0, 6.0);
					 g->DrawRectangle(Pens::Black, x[i]-12, y[i]-5, 3.0, 6.0);
					 g->DrawRectangle(Pens::Black, x[i]+9, y[i]-5, 3.0, 6.0);
					 Rotate(tu_img, g, td[i], x[i], y[i]-5);
					 // Draw health bars when required
					 if (hs[i] > 0)
					 {
						 g->FillRectangle(Brushes::Firebrick, x[i]-sx/2, y[i]-sy/2-11, (float)sx, 4.0);
						 if (ai[i])
							 g->FillRectangle(Brushes::Chartreuse, x[i]-sx/2, y[i]-sy/2-11, (float)sx*hp[i]/(hpi*hpr), 4.0);
						 else
							 g->FillRectangle(Brushes::Chartreuse, x[i]-sx/2, y[i]-sy/2-11, (float)sx*hp[i]/hpi, 4.0);
						 g->DrawRectangle(Pens::Black, x[i]-sx/2, y[i]-sy/2-11, (float)sx, 4.0);
						 hs[i]--;
					 }
					 // Fading death effect
					 if (recoil[i] > 385 && recoil[i] < 410)
					 {
						 SolidBrush * br = new SolidBrush(Color::FromArgb(255-(10*(recoil[i]-385)), this->BackColor));
						 g->FillRectangle(br, x[i]-sx/2, y[i]-sy/2, (float)sx, (float)sy);
					 }
				 }
				 // Projectile logic
				 for (int i = 0; i < pMax; i++)
				 {
					 if (pro_s[i] == 0)
						 continue;
					 // Draw laser path
					 Pen * p = new Pen(Color::Orange, 5);
					 SolidBrush * br = new SolidBrush(Color::Orange);
					 switch (pro_s[i])
					 {
					 case 5:
						 pro_s[i]--;
						 break;
					 case 4:
						 pro_s[i]--;
						 p->Width = 4;
						 break;
					 case 3:
						 pro_s[i]--;
						 p->Width = 3;
						 p->Color = Color::OrangeRed;
						 break;
					 case 2:
						 pro_s[i]--;
						 p->Width = 2;
						 p->Color = Color::OrangeRed;
						 break;
					 case 1:
						 pro_s[i]--;
						 p->Width = 1;
						 p->Color = Color::Red;
						 break;
					 }
					 g->DrawLine(p, px1[i], py1[i], px2[i], py2[i]);
					 if (pro_s[i] == 0)
						 px1[i] = -32;
					 // Draw laser splash effect
					 br->Color = p->Color;
					 PointF sps[] =
					 {
						 PointF(px2[i] - 9, py2[i] + 3),
						 PointF(px2[i] - 12, py2[i]),
						 PointF(px2[i] - 7, py2[i] + 1),
						 PointF(px2[i] - 9, py2[i] - 4),
						 PointF(px2[i] - 3, py2[i] - 2),
						 PointF(px2[i] + 3, py2[i] - 2),
						 PointF(px2[i] + 9, py2[i] - 4),
						 PointF(px2[i] + 7, py2[i] + 1),
						 PointF(px2[i] + 12, py2[i]),
						 PointF(px2[i] + 9, py2[i] + 3)
					 };
					 GraphicsPath * gp = new GraphicsPath();
					 gp->AddLines(sps);
					 Matrix * m = new Matrix();
					 m->RotateAt(pd[i]+180, PointF(px2[i], py2[i]));
					 gp->Transform(m);
					 g->FillPath(br, gp);
				 }
				 this->CreateGraphics()->DrawImage(bmp, 0, 0);
			 }

private: System::Void FastLoop_Tick(System::Object *  sender, System::EventArgs *  e)
		{
			for (int i = 0; i < tMax; i++)
			{
				if (!exists[i])
					continue;
				// Rotate turret
				if (ai[i])
					td[i] += dd[i];
				else
					td[i] += dd[i]*2;
				if (td[i] >= 360)
					td[i] -= 360;
				else if (td[i] < 0)
					td[i] += 360;
			}
		}

private: System::Void Control_MouseEnter(System::Object *  sender, System::EventArgs *  e)
		 {
			 dynamic_cast<Control*>(sender)->set_Font(new Drawing::Font("Microsoft Sans Serif", 8.25, FontStyle::Bold));
		 }

private: System::Void Control_MouseLeave(System::Object *  sender, System::EventArgs *  e)
		 {
			 dynamic_cast<Control*>(sender)->set_Font(new Drawing::Font("Microsoft Sans Serif", 8.25, FontStyle::Regular));
		 }

private: System::Void Settings_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 SDialog * settings = new SDialog();
			 settings->acs[0] = "Up";
			 settings->acs[1] = "Left";
			 settings->acs[2] = "Down";
			 settings->acs[3] = "Right";
			 settings->acs[4] = "Stop";
			 settings->acs[5] = "Turn clockwise";
			 settings->acs[6] = "Turn anticlockwise";
			 settings->acs[7] = "Fire";
			 settings->acs[8] = "Pause";
			 settings->kc[0,0] = U1;
			 settings->kc[1,0] = L1;
			 settings->kc[2,0] = D1;
			 settings->kc[3,0] = R1;
			 settings->kc[4,0] = ST1;
			 settings->kc[5,0] = RC1;
			 settings->kc[6,0] = RA1;
			 settings->kc[7,0] = S1;
			 settings->kc[8,0] = P1;
			 settings->kc[0,1] = U2;
			 settings->kc[1,1] = L2;
			 settings->kc[2,1] = D2;
			 settings->kc[3,1] = R2;
			 settings->kc[4,1] = ST2;
			 settings->kc[5,1] = RC2;
			 settings->kc[6,1] = RA2;
			 settings->kc[7,1] = S2;
			 settings->kc[8,1] = P2;
			 settings->ci = -1;
			 settings->MaxHP->Value = hpi;
			 settings->ShotDelay->Value = sdi;
			 settings->ReloadTime->Value = rlt;
			 settings->CartridgeSize->Value = crs;
			 settings->Dispersion->Value = d_max;
			 settings->ChangeRate->Value = dcr;
			 settings->HPRatio->Value = hpr;
			 for (int i = 0; i < settings->GeneralSettings->Controls->Count; i++)
			 {
				 if (settings->GeneralSettings->Controls->get_Item(i) != settings->DefaultGeneral)
					 settings->GeneralSettings->Controls->get_Item(i)->Enabled = !gsd;
			 }
			 switch (ds)
			 {
			 case 1:
				 settings->Easy->Checked = true;
				 break;
			 case 2:
				 settings->Normal->Checked = true;
				 break;
			 case 3:
				 settings->Hard->Checked = true;
				 break;
			 case 4:
				 settings->Custom->Checked = true;
				 settings->AISettings->Enabled = true;
				 settings->OtherSettings->Enabled = true;
				 break;
			 }
			 switch (ffs)
			 {
			 case 0:
				 settings->NoDamage->Checked = true;
				 break;
			 case 1:
				 settings->NormalDamage->Checked = true;
				 break;
			 case 2:
				 settings->ReactiveDamage->Checked = true;
				 break;
			 }
			 settings->T1->BackColor = cs[0];
			 settings->T2->BackColor = cs[1];
			 settings->T3->BackColor = cs[2];
			 settings->T4->BackColor = cs[3];
			 if (hpi == 10 && sdi == 50 && rlt == 150 && crs == 6)
				 settings->DefaultGeneral->Checked = true;
			 else
			 {
				 settings->DefaultGeneral->Checked = false;
				 for (int i = 0; i < settings->GeneralSettings->Controls->Count; i++)
					 settings->GeneralSettings->Controls->get_Item(i)->Enabled = true;
			 }
			 settings->tabControl->SelectedIndex = st;
			 settings->Left = this->Left + 64;
			 settings->Top = this->Top + 64;
			 settings->ShowDialog();
			 U1 = settings->kc[0,0];
			 L1 = settings->kc[1,0];
			 D1 = settings->kc[2,0];
			 R1 = settings->kc[3,0];
			 ST1 = settings->kc[4,0];
			 RC1 = settings->kc[5,0];
			 RA1 = settings->kc[6,0];
			 S1 = settings->kc[7,0];
			 P1 = settings->kc[8,0];
			 U2 = settings->kc[0,1];
			 L2 = settings->kc[1,1];
			 D2 = settings->kc[2,1];
			 R2 = settings->kc[3,1];
			 ST2 = settings->kc[4,1];
			 RC2 = settings->kc[5,1];
			 RA2 = settings->kc[6,1];
			 S2 = settings->kc[7,1];
			 P2 = settings->kc[8,1];
			 hpi = (int)settings->MaxHP->Value;
			 sdi = (int)settings->ShotDelay->Value;
			 rlt = (int)settings->ReloadTime->Value;
			 crs = (int)settings->CartridgeSize->Value;
			 d_max = (int)settings->Dispersion->Value;
			 dcr = (double)settings->ChangeRate->Value;
			 hpr = (double)settings->HPRatio->Value;
			 ds = settings->SetDifficulty();
			 gsd = settings->DefaultGeneral->Checked;
			 ffs = settings->SetFriendlyFire();
			 cs[0] = settings->T1->BackColor;
			 cs[1] = settings->T2->BackColor;
			 cs[2] = settings->T3->BackColor;
			 cs[3] = settings->T4->BackColor;
			 P1Label->ForeColor = cs[0];
			 P2Label->ForeColor = cs[1];
			 P3Label->ForeColor = cs[2];
			 P4Label->ForeColor = cs[3];
			 st = settings->tabControl->SelectedIndex;
		 }


private: System::Void Simulate_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 InitializeGame(false);
			 Graphics * g = this->CreateGraphics();
			 RectangleF rf = RectangleF(PointF(0,0), SizeF(this->Width, this->Height - 40));
			 StringFormat * sf = new StringFormat();
			 sf->Alignment = StringAlignment::Center;
			 sf->LineAlignment = StringAlignment::Center;
			 g->DrawString("Add tanks to the field by clicking on the point you wish to place them.\nPress [ESC] at any time to discard changes and return to the main menu.\nPress [ENTER] when done to begin the game with only AI.\nPress [1] or [2] (not on NumPad) to begin with human player(s).", this->Font, Brushes::Black, rf, sf);
			 ct = 0;
			 EditMode = true;
			 EditorLoop->Enabled = true;
			 this->set_Cursor(cur);
		 }

private: System::Void Form1_MouseMove(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 ex = e->X;
			 ey = e->Y;
		 }

private: System::Void Form1_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (EditMode)
			 {
				 if (!CheckBoundaries(ct, TMAX))
				 {
					 td[ct] = r->Next(0,359);
					 exists[ct] = true;
					 ct++;
				 }
				 if (ct >= TMAX)
					 MessageBox::Show(String::Concat("Tank limit reached! You can place a maximum of ", TMAX.ToString(), " tanks.\nPress [ENTER] to begin the game with only AI.\nPress [1] or [2] (not on NumPad) to begin with human player(s)."), "LaserTanks", MessageBoxButtons::OK, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button1);
			 }
		 }

private: System::Void EditorLoop_Tick(System::Object *  sender, System::EventArgs *  e)
		 {
			// Bitmap initialized once only in Form1 constructor to prevent memory escalation
			 Graphics * g = Graphics::FromImage(bmp); // Double-buffered to prevent flashing
			 g->Clear(this->BackColor);
			RectangleF rf = RectangleF(PointF(0,0), SizeF(this->Width, this->Height - 40));
			StringFormat * sf = new StringFormat();
			sf->Alignment = StringAlignment::Center;
			sf->LineAlignment = StringAlignment::Center;
			if (ct == 0)
				g->DrawString("Add tanks to the field by clicking on the point you wish to place them.\nPress [ESC] at any time to discard changes and return to the main menu.\nPress [ENTER] when done to begin the game with only AI.\nPress [1] or [2] (not on NumPad) to begin with human player(s).", this->Font, Brushes::Black, rf, sf);
			if (ct < TMAX) // Array logic MUST be prevented at all costs when ct is out of its range
			{
				x[ct] = ex;
				y[ct] = ey;
				td[ct] = 0;
				if (CheckBoundaries(ct, TMAX))
					t_img[ct] = TankImage->Images->get_Item(1);
				else
					t_img[ct] = TankImage->Images->get_Item(0);
				for (int i = 0; i <= ct; i++)
				{
					g->DrawImageUnscaled(t_img[i], Point((float)x[i]-sx/2, (float)y[i]-sy/2));
					SolidBrush * br = new SolidBrush(Color::Black);
					br->Color = cs[i];
					g->FillRectangle(br, x[i]-12, y[i]-5, 3.0, 6.0);
					g->FillRectangle(br, x[i]+9, y[i]-5, 3.0, 6.0);
					g->DrawRectangle(Pens::Black, x[i]-12, y[i]-5, 3.0, 6.0);
					g->DrawRectangle(Pens::Black, x[i]+9, y[i]-5, 3.0, 6.0);
					Rotate(tu_img, g, td[i], x[i], y[i]-5);
				}
			}
			else
			{
				for (int i = 0; i < TMAX; i++)
				{
					g->DrawImageUnscaled(t_img[i], Point((float)x[i]-sx/2, (float)y[i]-sy/2));
					SolidBrush * br = new SolidBrush(Color::Black);
					br->Color = cs[i];
					g->FillRectangle(br, x[i]-12, y[i]-5, 3.0, 6.0);
					g->FillRectangle(br, x[i]+9, y[i]-5, 3.0, 6.0);
					g->DrawRectangle(Pens::Black, x[i]-12, y[i]-5, 3.0, 6.0);
					g->DrawRectangle(Pens::Black, x[i]+9, y[i]-5, 3.0, 6.0);
					Rotate(tu_img, g, td[i], x[i], y[i]-5);
				}
			}
			this->CreateGraphics()->DrawImage(bmp, 0, 0);
		 }

private: System::Void Form1_Resize(System::Object *  sender, System::EventArgs *  e)
		 {
			xr = this->Width - 24 - sx/2;
			yb = this->Height - 48 - sy/2;
			VictoryLabel->Left = this->Width/2 - 92;
			VictoryLabel->Top = (this->Height - 34)/2 - 12;
			Start1P->Left = VictoryLabel->Left - 8;
			Simulate->Left = VictoryLabel->Left - 8;
			Start2P->Left = VictoryLabel->Left + 96;
			Settings->Left = VictoryLabel->Left + 96;
			Start1P->Top = VictoryLabel->Top - 32;
			Start2P->Top = VictoryLabel->Top - 32;
			Simulate->Top = VictoryLabel->Top + 32;
			Settings->Top = VictoryLabel->Top + 32;
			P1Label->Top = this->Height - 162;
			P2Label->Left = this->Width - 160;
			P4Label->Left = this->Width - 160;
			P4Label->Top = this->Height - 162;
			P1Title->Top = P1Label->Top + P1Label->Height; 
			P2Title->Left = P2Label->Left;
			P4Title->Left = P4Label->Left;
			P4Title->Top = P4Label->Top + P4Label->Height;
		 }

private: System::Void P1Label_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 int i = Convert::ToInt32(P1Label->Text);
			 switch (e->Button)
			 {
			 case MouseButtons::Left:
				i++;
				if (i > 4)
					i = 1;
				break;
			 case MouseButtons::Right:
				 i--;
				 if (i < 1)
					 i = 4;
			 }
			 P1Label->Text = i.ToString();
			 P1Label->ForeColor = cs[i-1];
		 }

private: System::Void P2Label_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 int i = Convert::ToInt32(P2Label->Text);
			 switch (e->Button)
			 {
			 case MouseButtons::Left:
				i++;
				if (i > 4)
					i = 1;
				break;
			 case MouseButtons::Right:
				 i--;
				 if (i < 1)
					 i = 4;
			 }
			 P2Label->Text = i.ToString();
			 P2Label->ForeColor = cs[i-1];
		 }

private: System::Void P3Label_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 int i = Convert::ToInt32(P3Label->Text);
			 switch (e->Button)
			 {
			 case MouseButtons::Left:
				i++;
				if (i > 4)
					i = 1;
				break;
			 case MouseButtons::Right:
				 i--;
				 if (i < 1)
					 i = 4;
			 }
			 P3Label->Text = i.ToString();
			 P3Label->ForeColor = cs[i-1];
		 }

private: System::Void P4Label_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 int i = Convert::ToInt32(P4Label->Text);
			 switch (e->Button)
			 {
			 case MouseButtons::Left:
				i++;
				if (i > 4)
					i = 1;
				break;
			 case MouseButtons::Right:
				 i--;
				 if (i < 1)
					 i = 4;
			 }
			 P4Label->Text = i.ToString();
			 P4Label->ForeColor = cs[i-1];
		 }

};
}


