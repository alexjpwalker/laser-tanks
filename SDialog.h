#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace LaserTanks
{
	public __gc class SDialog : public System::Windows::Forms::Form
	{
	public: 
		SDialog(void)
		{
			InitializeComponent();
			kc = new int __gc[9,2];
			acs = new String * __gc[9];
		}
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		} // TODO: Publicize all controls (no exceptions)

	public:
	int ri, ci; // row/column index
	int kc __gc[,];
	static bool tablock = false;
	static Random * r = new Random();
	String * acs __gc[];

	public: System::Windows::Forms::TabControl *  tabControl;
	public: System::Windows::Forms::TabPage *  GameOptions;
	public: System::Windows::Forms::RadioButton *  Easy;
	public: System::Windows::Forms::RadioButton *  Normal;
	public: System::Windows::Forms::RadioButton *  Hard;
	public: System::Windows::Forms::GroupBox *  Difficulty;
	public: System::Windows::Forms::RadioButton *  Custom;
	public: System::Windows::Forms::GroupBox *  GeneralSettings;
	public: System::Windows::Forms::NumericUpDown *  MaxHP;
	public: System::Windows::Forms::Label *  t_mhp;
	public: System::Windows::Forms::TabPage *  GameControls;
	public: System::Windows::Forms::Label *  t_sd;
	public: System::Windows::Forms::NumericUpDown *  ShotDelay;
	public: System::Windows::Forms::NumericUpDown *  ReloadTime;
	public: System::Windows::Forms::NumericUpDown *  CartridgeSize;
	public: System::Windows::Forms::Label *  t_rlt;
	public: System::Windows::Forms::Label *  t_crs;
	public: System::Windows::Forms::Button *  DefaultP1;
	public: System::Windows::Forms::Button *  DefaultP2;
	public: System::Windows::Forms::GroupBox *  AISettings;
	public: System::Windows::Forms::Button *  DefaultAI;
	public: System::Windows::Forms::NumericUpDown *  ChangeRate;
	public: System::Windows::Forms::Label *  t_dcr;
	public: System::Windows::Forms::Label *  t_disp;
	public: System::Windows::Forms::NumericUpDown *  Dispersion;
	public: System::Windows::Forms::GroupBox *  OtherSettings;
	public: System::Windows::Forms::Label *  t_pickups;
	public: System::Windows::Forms::Label *  t_hpd;
	public: System::Windows::Forms::NumericUpDown *  HPRatio;
	public: System::Windows::Forms::ComboBox *  Pickups;
	public: System::Windows::Forms::Button *  DefaultOther;
	public: System::Windows::Forms::CheckBox *  DefaultGeneral;
	public: System::Windows::Forms::TabPage *  TeamSettings;
	public: System::Windows::Forms::GroupBox *  FriendlyFire;
	public: System::Windows::Forms::RadioButton *  NoDamage;
	public: System::Windows::Forms::RadioButton *  NormalDamage;
	public: System::Windows::Forms::RadioButton *  ReactiveDamage;
	public: System::Windows::Forms::Label *  T1;
	public: System::Windows::Forms::Label *  T2;
	public: System::Windows::Forms::Label *  T3;
	public: System::Windows::Forms::Label *  T4;
	public: System::Windows::Forms::ColorDialog *  CDialog;

	public:
		System::ComponentModel::Container* components;

		void InitializeComponent(void)
		{
			this->tabControl = new System::Windows::Forms::TabControl();
			this->GameOptions = new System::Windows::Forms::TabPage();
			this->OtherSettings = new System::Windows::Forms::GroupBox();
			this->Pickups = new System::Windows::Forms::ComboBox();
			this->DefaultOther = new System::Windows::Forms::Button();
			this->t_pickups = new System::Windows::Forms::Label();
			this->t_hpd = new System::Windows::Forms::Label();
			this->HPRatio = new System::Windows::Forms::NumericUpDown();
			this->AISettings = new System::Windows::Forms::GroupBox();
			this->DefaultAI = new System::Windows::Forms::Button();
			this->ChangeRate = new System::Windows::Forms::NumericUpDown();
			this->t_dcr = new System::Windows::Forms::Label();
			this->t_disp = new System::Windows::Forms::Label();
			this->Dispersion = new System::Windows::Forms::NumericUpDown();
			this->GeneralSettings = new System::Windows::Forms::GroupBox();
			this->DefaultGeneral = new System::Windows::Forms::CheckBox();
			this->CartridgeSize = new System::Windows::Forms::NumericUpDown();
			this->ReloadTime = new System::Windows::Forms::NumericUpDown();
			this->t_rlt = new System::Windows::Forms::Label();
			this->t_crs = new System::Windows::Forms::Label();
			this->ShotDelay = new System::Windows::Forms::NumericUpDown();
			this->t_sd = new System::Windows::Forms::Label();
			this->t_mhp = new System::Windows::Forms::Label();
			this->MaxHP = new System::Windows::Forms::NumericUpDown();
			this->Difficulty = new System::Windows::Forms::GroupBox();
			this->Custom = new System::Windows::Forms::RadioButton();
			this->Easy = new System::Windows::Forms::RadioButton();
			this->Normal = new System::Windows::Forms::RadioButton();
			this->Hard = new System::Windows::Forms::RadioButton();
			this->GameControls = new System::Windows::Forms::TabPage();
			this->DefaultP2 = new System::Windows::Forms::Button();
			this->DefaultP1 = new System::Windows::Forms::Button();
			this->TeamSettings = new System::Windows::Forms::TabPage();
			this->T4 = new System::Windows::Forms::Label();
			this->T3 = new System::Windows::Forms::Label();
			this->T2 = new System::Windows::Forms::Label();
			this->T1 = new System::Windows::Forms::Label();
			this->FriendlyFire = new System::Windows::Forms::GroupBox();
			this->ReactiveDamage = new System::Windows::Forms::RadioButton();
			this->NormalDamage = new System::Windows::Forms::RadioButton();
			this->NoDamage = new System::Windows::Forms::RadioButton();
			this->CDialog = new System::Windows::Forms::ColorDialog();
			this->tabControl->SuspendLayout();
			this->GameOptions->SuspendLayout();
			this->OtherSettings->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->HPRatio))->BeginInit();
			this->AISettings->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->ChangeRate))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->Dispersion))->BeginInit();
			this->GeneralSettings->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->CartridgeSize))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->ReloadTime))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->ShotDelay))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->MaxHP))->BeginInit();
			this->Difficulty->SuspendLayout();
			this->GameControls->SuspendLayout();
			this->TeamSettings->SuspendLayout();
			this->FriendlyFire->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->GameOptions);
			this->tabControl->Controls->Add(this->GameControls);
			this->tabControl->Controls->Add(this->TeamSettings);
			this->tabControl->HotTrack = true;
			this->tabControl->Location = System::Drawing::Point(8, 8);
			this->tabControl->Multiline = true;
			this->tabControl->Name = S"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(296, 320);
			this->tabControl->TabIndex = 0;
			this->tabControl->KeyDown += new System::Windows::Forms::KeyEventHandler(this, tabControl_KeyDown);
			this->tabControl->MouseDown += new System::Windows::Forms::MouseEventHandler(this, tabControl_MouseDown);
			this->tabControl->SelectedIndexChanged += new System::EventHandler(this, tabControl_SelectedIndexChanged);
			// 
			// GameOptions
			// 
			this->GameOptions->Controls->Add(this->OtherSettings);
			this->GameOptions->Controls->Add(this->AISettings);
			this->GameOptions->Controls->Add(this->GeneralSettings);
			this->GameOptions->Controls->Add(this->Difficulty);
			this->GameOptions->Location = System::Drawing::Point(4, 22);
			this->GameOptions->Name = S"GameOptions";
			this->GameOptions->Size = System::Drawing::Size(288, 294);
			this->GameOptions->TabIndex = 0;
			this->GameOptions->Text = S"Game Options";
			// 
			// OtherSettings
			// 
			this->OtherSettings->Controls->Add(this->Pickups);
			this->OtherSettings->Controls->Add(this->DefaultOther);
			this->OtherSettings->Controls->Add(this->t_pickups);
			this->OtherSettings->Controls->Add(this->t_hpd);
			this->OtherSettings->Controls->Add(this->HPRatio);
			this->OtherSettings->Enabled = false;
			this->OtherSettings->Location = System::Drawing::Point(152, 168);
			this->OtherSettings->Name = S"OtherSettings";
			this->OtherSettings->Size = System::Drawing::Size(136, 120);
			this->OtherSettings->TabIndex = 6;
			this->OtherSettings->TabStop = false;
			this->OtherSettings->Text = S"Other Settings";
			// 
			// Pickups
			// 
			System::Object* __mcTemp__1[] = new System::Object*[1];
			__mcTemp__1[0] = S"None";
			this->Pickups->Items->AddRange(__mcTemp__1);
			this->Pickups->Location = System::Drawing::Point(64, 56);
			this->Pickups->Name = S"Pickups";
			this->Pickups->Size = System::Drawing::Size(64, 21);
			this->Pickups->TabIndex = 9;
			this->Pickups->Text = S"None";
			// 
			// DefaultOther
			// 
			this->DefaultOther->Location = System::Drawing::Point(32, 88);
			this->DefaultOther->Name = S"DefaultOther";
			this->DefaultOther->Size = System::Drawing::Size(72, 24);
			this->DefaultOther->TabIndex = 8;
			this->DefaultOther->Text = S"Default";
			this->DefaultOther->Click += new System::EventHandler(this, DefaultOther_Click);
			// 
			// t_pickups
			// 
			this->t_pickups->Location = System::Drawing::Point(8, 48);
			this->t_pickups->Name = S"t_pickups";
			this->t_pickups->Size = System::Drawing::Size(56, 32);
			this->t_pickups->TabIndex = 2;
			this->t_pickups->Text = S"Pickups:";
			this->t_pickups->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// t_hpd
			// 
			this->t_hpd->Location = System::Drawing::Point(8, 24);
			this->t_hpd->Name = S"t_hpd";
			this->t_hpd->Size = System::Drawing::Size(64, 24);
			this->t_hpd->TabIndex = 1;
			this->t_hpd->Text = S"AI/human HP ratio:";
			this->t_hpd->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// HPRatio
			// 
			this->HPRatio->DecimalPlaces = 1;
			System::Int32 __mcTemp__2[] = new System::Int32[4];
			__mcTemp__2[0] = 1;
			__mcTemp__2[1] = 0;
			__mcTemp__2[2] = 0;
			__mcTemp__2[3] = 65536;
			this->HPRatio->Increment = System::Decimal(__mcTemp__2);
			this->HPRatio->Location = System::Drawing::Point(80, 24);
			System::Int32 __mcTemp__3[] = new System::Int32[4];
			__mcTemp__3[0] = 10;
			__mcTemp__3[1] = 0;
			__mcTemp__3[2] = 0;
			__mcTemp__3[3] = 0;
			this->HPRatio->Maximum = System::Decimal(__mcTemp__3);
			System::Int32 __mcTemp__4[] = new System::Int32[4];
			__mcTemp__4[0] = 1;
			__mcTemp__4[1] = 0;
			__mcTemp__4[2] = 0;
			__mcTemp__4[3] = 65536;
			this->HPRatio->Minimum = System::Decimal(__mcTemp__4);
			this->HPRatio->Name = S"HPRatio";
			this->HPRatio->Size = System::Drawing::Size(48, 20);
			this->HPRatio->TabIndex = 0;
			System::Int32 __mcTemp__5[] = new System::Int32[4];
			__mcTemp__5[0] = 1;
			__mcTemp__5[1] = 0;
			__mcTemp__5[2] = 0;
			__mcTemp__5[3] = 0;
			this->HPRatio->Value = System::Decimal(__mcTemp__5);
			// 
			// AISettings
			// 
			this->AISettings->Controls->Add(this->DefaultAI);
			this->AISettings->Controls->Add(this->ChangeRate);
			this->AISettings->Controls->Add(this->t_dcr);
			this->AISettings->Controls->Add(this->t_disp);
			this->AISettings->Controls->Add(this->Dispersion);
			this->AISettings->Enabled = false;
			this->AISettings->Location = System::Drawing::Point(8, 168);
			this->AISettings->Name = S"AISettings";
			this->AISettings->Size = System::Drawing::Size(136, 120);
			this->AISettings->TabIndex = 5;
			this->AISettings->TabStop = false;
			this->AISettings->Text = S"AI Settings";
			// 
			// DefaultAI
			// 
			this->DefaultAI->Location = System::Drawing::Point(32, 88);
			this->DefaultAI->Name = S"DefaultAI";
			this->DefaultAI->Size = System::Drawing::Size(72, 24);
			this->DefaultAI->TabIndex = 8;
			this->DefaultAI->Text = S"Default";
			this->DefaultAI->Click += new System::EventHandler(this, DefaultAI_Click);
			// 
			// ChangeRate
			// 
			this->ChangeRate->DecimalPlaces = 2;
			System::Int32 __mcTemp__6[] = new System::Int32[4];
			__mcTemp__6[0] = 1;
			__mcTemp__6[1] = 0;
			__mcTemp__6[2] = 0;
			__mcTemp__6[3] = 131072;
			this->ChangeRate->Increment = System::Decimal(__mcTemp__6);
			this->ChangeRate->Location = System::Drawing::Point(80, 56);
			System::Int32 __mcTemp__7[] = new System::Int32[4];
			__mcTemp__7[0] = 1;
			__mcTemp__7[1] = 0;
			__mcTemp__7[2] = 0;
			__mcTemp__7[3] = 0;
			this->ChangeRate->Maximum = System::Decimal(__mcTemp__7);
			this->ChangeRate->Name = S"ChangeRate";
			this->ChangeRate->Size = System::Drawing::Size(48, 20);
			this->ChangeRate->TabIndex = 3;
			System::Int32 __mcTemp__8[] = new System::Int32[4];
			__mcTemp__8[0] = 10;
			__mcTemp__8[1] = 0;
			__mcTemp__8[2] = 0;
			__mcTemp__8[3] = 131072;
			this->ChangeRate->Value = System::Decimal(__mcTemp__8);
			// 
			// t_dcr
			// 
			this->t_dcr->Location = System::Drawing::Point(8, 48);
			this->t_dcr->Name = S"t_dcr";
			this->t_dcr->Size = System::Drawing::Size(72, 32);
			this->t_dcr->TabIndex = 2;
			this->t_dcr->Text = S"Direction change rate:";
			this->t_dcr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// t_disp
			// 
			this->t_disp->Location = System::Drawing::Point(16, 24);
			this->t_disp->Name = S"t_disp";
			this->t_disp->Size = System::Drawing::Size(64, 16);
			this->t_disp->TabIndex = 1;
			this->t_disp->Text = S"Dispersion:";
			this->t_disp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Dispersion
			// 
			this->Dispersion->Location = System::Drawing::Point(80, 24);
			System::Int32 __mcTemp__9[] = new System::Int32[4];
			__mcTemp__9[0] = 45;
			__mcTemp__9[1] = 0;
			__mcTemp__9[2] = 0;
			__mcTemp__9[3] = 0;
			this->Dispersion->Maximum = System::Decimal(__mcTemp__9);
			this->Dispersion->Name = S"Dispersion";
			this->Dispersion->Size = System::Drawing::Size(48, 20);
			this->Dispersion->TabIndex = 0;
			System::Int32 __mcTemp__10[] = new System::Int32[4];
			__mcTemp__10[0] = 5;
			__mcTemp__10[1] = 0;
			__mcTemp__10[2] = 0;
			__mcTemp__10[3] = 0;
			this->Dispersion->Value = System::Decimal(__mcTemp__10);
			// 
			// GeneralSettings
			// 
			this->GeneralSettings->Controls->Add(this->DefaultGeneral);
			this->GeneralSettings->Controls->Add(this->CartridgeSize);
			this->GeneralSettings->Controls->Add(this->ReloadTime);
			this->GeneralSettings->Controls->Add(this->t_rlt);
			this->GeneralSettings->Controls->Add(this->t_crs);
			this->GeneralSettings->Controls->Add(this->ShotDelay);
			this->GeneralSettings->Controls->Add(this->t_sd);
			this->GeneralSettings->Controls->Add(this->t_mhp);
			this->GeneralSettings->Controls->Add(this->MaxHP);
			this->GeneralSettings->Location = System::Drawing::Point(112, 8);
			this->GeneralSettings->Name = S"GeneralSettings";
			this->GeneralSettings->Size = System::Drawing::Size(160, 144);
			this->GeneralSettings->TabIndex = 4;
			this->GeneralSettings->TabStop = false;
			this->GeneralSettings->Text = S"General Settings";
			// 
			// DefaultGeneral
			// 
			this->DefaultGeneral->Checked = true;
			this->DefaultGeneral->CheckState = System::Windows::Forms::CheckState::Checked;
			this->DefaultGeneral->Location = System::Drawing::Point(24, 120);
			this->DefaultGeneral->Name = S"DefaultGeneral";
			this->DefaultGeneral->Size = System::Drawing::Size(128, 16);
			this->DefaultGeneral->TabIndex = 8;
			this->DefaultGeneral->Text = S"Use default settings";
			this->DefaultGeneral->CheckedChanged += new System::EventHandler(this, DefaultGeneral_CheckedChanged);
			// 
			// CartridgeSize
			// 
			this->CartridgeSize->Enabled = false;
			this->CartridgeSize->Location = System::Drawing::Point(88, 96);
			System::Int32 __mcTemp__11[] = new System::Int32[4];
			__mcTemp__11[0] = 999;
			__mcTemp__11[1] = 0;
			__mcTemp__11[2] = 0;
			__mcTemp__11[3] = 0;
			this->CartridgeSize->Maximum = System::Decimal(__mcTemp__11);
			System::Int32 __mcTemp__12[] = new System::Int32[4];
			__mcTemp__12[0] = 2;
			__mcTemp__12[1] = 0;
			__mcTemp__12[2] = 0;
			__mcTemp__12[3] = 0;
			this->CartridgeSize->Minimum = System::Decimal(__mcTemp__12);
			this->CartridgeSize->Name = S"CartridgeSize";
			this->CartridgeSize->Size = System::Drawing::Size(48, 20);
			this->CartridgeSize->TabIndex = 7;
			System::Int32 __mcTemp__13[] = new System::Int32[4];
			__mcTemp__13[0] = 6;
			__mcTemp__13[1] = 0;
			__mcTemp__13[2] = 0;
			__mcTemp__13[3] = 0;
			this->CartridgeSize->Value = System::Decimal(__mcTemp__13);
			this->CartridgeSize->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, General_KeyPress);
			this->CartridgeSize->ValueChanged += new System::EventHandler(this, General_ValueChanged);
			// 
			// ReloadTime
			// 
			this->ReloadTime->Enabled = false;
			this->ReloadTime->Location = System::Drawing::Point(88, 72);
			System::Int32 __mcTemp__14[] = new System::Int32[4];
			__mcTemp__14[0] = 999;
			__mcTemp__14[1] = 0;
			__mcTemp__14[2] = 0;
			__mcTemp__14[3] = 0;
			this->ReloadTime->Maximum = System::Decimal(__mcTemp__14);
			System::Int32 __mcTemp__15[] = new System::Int32[4];
			__mcTemp__15[0] = 6;
			__mcTemp__15[1] = 0;
			__mcTemp__15[2] = 0;
			__mcTemp__15[3] = 0;
			this->ReloadTime->Minimum = System::Decimal(__mcTemp__15);
			this->ReloadTime->Name = S"ReloadTime";
			this->ReloadTime->Size = System::Drawing::Size(48, 20);
			this->ReloadTime->TabIndex = 6;
			System::Int32 __mcTemp__16[] = new System::Int32[4];
			__mcTemp__16[0] = 150;
			__mcTemp__16[1] = 0;
			__mcTemp__16[2] = 0;
			__mcTemp__16[3] = 0;
			this->ReloadTime->Value = System::Decimal(__mcTemp__16);
			this->ReloadTime->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, General_KeyPress);
			this->ReloadTime->ValueChanged += new System::EventHandler(this, General_ValueChanged);
			// 
			// t_rlt
			// 
			this->t_rlt->Enabled = false;
			this->t_rlt->Location = System::Drawing::Point(8, 72);
			this->t_rlt->Name = S"t_rlt";
			this->t_rlt->Size = System::Drawing::Size(80, 16);
			this->t_rlt->TabIndex = 5;
			this->t_rlt->Text = S"Reload time:";
			this->t_rlt->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// t_crs
			// 
			this->t_crs->Enabled = false;
			this->t_crs->Location = System::Drawing::Point(8, 96);
			this->t_crs->Name = S"t_crs";
			this->t_crs->Size = System::Drawing::Size(78, 16);
			this->t_crs->TabIndex = 4;
			this->t_crs->Text = S"Cartridge size:";
			this->t_crs->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// ShotDelay
			// 
			this->ShotDelay->Enabled = false;
			this->ShotDelay->Location = System::Drawing::Point(88, 48);
			System::Int32 __mcTemp__17[] = new System::Int32[4];
			__mcTemp__17[0] = 999;
			__mcTemp__17[1] = 0;
			__mcTemp__17[2] = 0;
			__mcTemp__17[3] = 0;
			this->ShotDelay->Maximum = System::Decimal(__mcTemp__17);
			System::Int32 __mcTemp__18[] = new System::Int32[4];
			__mcTemp__18[0] = 6;
			__mcTemp__18[1] = 0;
			__mcTemp__18[2] = 0;
			__mcTemp__18[3] = 0;
			this->ShotDelay->Minimum = System::Decimal(__mcTemp__18);
			this->ShotDelay->Name = S"ShotDelay";
			this->ShotDelay->Size = System::Drawing::Size(48, 20);
			this->ShotDelay->TabIndex = 3;
			System::Int32 __mcTemp__19[] = new System::Int32[4];
			__mcTemp__19[0] = 50;
			__mcTemp__19[1] = 0;
			__mcTemp__19[2] = 0;
			__mcTemp__19[3] = 0;
			this->ShotDelay->Value = System::Decimal(__mcTemp__19);
			this->ShotDelay->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, General_KeyPress);
			this->ShotDelay->ValueChanged += new System::EventHandler(this, General_ValueChanged);
			// 
			// t_sd
			// 
			this->t_sd->Enabled = false;
			this->t_sd->Location = System::Drawing::Point(16, 48);
			this->t_sd->Name = S"t_sd";
			this->t_sd->Size = System::Drawing::Size(64, 16);
			this->t_sd->TabIndex = 2;
			this->t_sd->Text = S"Shot delay:";
			this->t_sd->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// t_mhp
			// 
			this->t_mhp->Enabled = false;
			this->t_mhp->Location = System::Drawing::Point(24, 24);
			this->t_mhp->Name = S"t_mhp";
			this->t_mhp->Size = System::Drawing::Size(56, 16);
			this->t_mhp->TabIndex = 1;
			this->t_mhp->Text = S"Max HP:";
			this->t_mhp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// MaxHP
			// 
			this->MaxHP->Enabled = false;
			this->MaxHP->Location = System::Drawing::Point(88, 24);
			System::Int32 __mcTemp__20[] = new System::Int32[4];
			__mcTemp__20[0] = 999;
			__mcTemp__20[1] = 0;
			__mcTemp__20[2] = 0;
			__mcTemp__20[3] = 0;
			this->MaxHP->Maximum = System::Decimal(__mcTemp__20);
			System::Int32 __mcTemp__21[] = new System::Int32[4];
			__mcTemp__21[0] = 1;
			__mcTemp__21[1] = 0;
			__mcTemp__21[2] = 0;
			__mcTemp__21[3] = 0;
			this->MaxHP->Minimum = System::Decimal(__mcTemp__21);
			this->MaxHP->Name = S"MaxHP";
			this->MaxHP->Size = System::Drawing::Size(48, 20);
			this->MaxHP->TabIndex = 0;
			System::Int32 __mcTemp__22[] = new System::Int32[4];
			__mcTemp__22[0] = 10;
			__mcTemp__22[1] = 0;
			__mcTemp__22[2] = 0;
			__mcTemp__22[3] = 0;
			this->MaxHP->Value = System::Decimal(__mcTemp__22);
			this->MaxHP->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, General_KeyPress);
			this->MaxHP->ValueChanged += new System::EventHandler(this, General_ValueChanged);
			// 
			// Difficulty
			// 
			this->Difficulty->Controls->Add(this->Custom);
			this->Difficulty->Controls->Add(this->Easy);
			this->Difficulty->Controls->Add(this->Normal);
			this->Difficulty->Controls->Add(this->Hard);
			this->Difficulty->Location = System::Drawing::Point(16, 8);
			this->Difficulty->Name = S"Difficulty";
			this->Difficulty->Size = System::Drawing::Size(88, 128);
			this->Difficulty->TabIndex = 3;
			this->Difficulty->TabStop = false;
			this->Difficulty->Text = S"Difficulty";
			// 
			// Custom
			// 
			this->Custom->Location = System::Drawing::Point(16, 96);
			this->Custom->Name = S"Custom";
			this->Custom->Size = System::Drawing::Size(64, 16);
			this->Custom->TabIndex = 3;
			this->Custom->Text = S"Custom";
			this->Custom->CheckedChanged += new System::EventHandler(this, Custom_CheckedChanged);
			// 
			// Easy
			// 
			this->Easy->Location = System::Drawing::Point(16, 24);
			this->Easy->Name = S"Easy";
			this->Easy->Size = System::Drawing::Size(64, 16);
			this->Easy->TabIndex = 0;
			this->Easy->Text = S"Easy";
			this->Easy->CheckedChanged += new System::EventHandler(this, Easy_CheckedChanged);
			// 
			// Normal
			// 
			this->Normal->Location = System::Drawing::Point(16, 48);
			this->Normal->Name = S"Normal";
			this->Normal->Size = System::Drawing::Size(64, 16);
			this->Normal->TabIndex = 1;
			this->Normal->Text = S"Normal";
			this->Normal->CheckedChanged += new System::EventHandler(this, Normal_CheckedChanged);
			// 
			// Hard
			// 
			this->Hard->Location = System::Drawing::Point(16, 72);
			this->Hard->Name = S"Hard";
			this->Hard->Size = System::Drawing::Size(64, 16);
			this->Hard->TabIndex = 2;
			this->Hard->Text = S"Hard";
			this->Hard->CheckedChanged += new System::EventHandler(this, Hard_CheckedChanged);
			// 
			// GameControls
			// 
			this->GameControls->Controls->Add(this->DefaultP2);
			this->GameControls->Controls->Add(this->DefaultP1);
			this->GameControls->Location = System::Drawing::Point(4, 22);
			this->GameControls->Name = S"GameControls";
			this->GameControls->Size = System::Drawing::Size(288, 294);
			this->GameControls->TabIndex = 1;
			this->GameControls->Text = S"Game Controls";
			this->GameControls->MouseUp += new System::Windows::Forms::MouseEventHandler(this, GameControls_MouseUp);
			this->GameControls->Paint += new System::Windows::Forms::PaintEventHandler(this, GameControls_Paint);
			// 
			// DefaultP2
			// 
			this->DefaultP2->Location = System::Drawing::Point(200, 264);
			this->DefaultP2->Name = S"DefaultP2";
			this->DefaultP2->TabIndex = 1;
			this->DefaultP2->Text = S"Default";
			this->DefaultP2->Click += new System::EventHandler(this, DefaultP2_Click);
			// 
			// DefaultP1
			// 
			this->DefaultP1->Location = System::Drawing::Point(96, 264);
			this->DefaultP1->Name = S"DefaultP1";
			this->DefaultP1->TabIndex = 0;
			this->DefaultP1->Text = S"Default";
			this->DefaultP1->Click += new System::EventHandler(this, DefaultP1_Click);
			// 
			// TeamSettings
			// 
			this->TeamSettings->Controls->Add(this->T4);
			this->TeamSettings->Controls->Add(this->T3);
			this->TeamSettings->Controls->Add(this->T2);
			this->TeamSettings->Controls->Add(this->T1);
			this->TeamSettings->Controls->Add(this->FriendlyFire);
			this->TeamSettings->Location = System::Drawing::Point(4, 22);
			this->TeamSettings->Name = S"TeamSettings";
			this->TeamSettings->Size = System::Drawing::Size(288, 294);
			this->TeamSettings->TabIndex = 2;
			this->TeamSettings->Text = S"Team Settings";
			// 
			// T4
			// 
			this->T4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->T4->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 8.25F, (System::Drawing::FontStyle)(System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline), System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->T4->Location = System::Drawing::Point(144, 200);
			this->T4->Name = S"T4";
			this->T4->Size = System::Drawing::Size(88, 64);
			this->T4->TabIndex = 4;
			this->T4->Text = S"Team 4";
			this->T4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->T4->Click += new System::EventHandler(this, T4_Click);
			this->T4->DoubleClick += new System::EventHandler(this, T4_DoubleClick);
			// 
			// T3
			// 
			this->T3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->T3->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 8.25F, (System::Drawing::FontStyle)(System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline), System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->T3->Location = System::Drawing::Point(56, 200);
			this->T3->Name = S"T3";
			this->T3->Size = System::Drawing::Size(88, 64);
			this->T3->TabIndex = 3;
			this->T3->Text = S"Team 3";
			this->T3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->T3->Click += new System::EventHandler(this, T3_Click);
			this->T3->DoubleClick += new System::EventHandler(this, T3_DoubleClick);
			// 
			// T2
			// 
			this->T2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->T2->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 8.25F, (System::Drawing::FontStyle)(System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline), System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->T2->Location = System::Drawing::Point(144, 136);
			this->T2->Name = S"T2";
			this->T2->Size = System::Drawing::Size(88, 64);
			this->T2->TabIndex = 2;
			this->T2->Text = S"Team 2";
			this->T2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->T2->Click += new System::EventHandler(this, T2_Click);
			this->T2->DoubleClick += new System::EventHandler(this, T2_DoubleClick);
			// 
			// T1
			// 
			this->T1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->T1->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 8.25F, (System::Drawing::FontStyle)(System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline), System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->T1->Location = System::Drawing::Point(56, 136);
			this->T1->Name = S"T1";
			this->T1->Size = System::Drawing::Size(88, 64);
			this->T1->TabIndex = 1;
			this->T1->Text = S"Team 1";
			this->T1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->T1->Click += new System::EventHandler(this, T1_Click);
			this->T1->DoubleClick += new System::EventHandler(this, T1_DoubleClick);
			// 
			// FriendlyFire
			// 
			this->FriendlyFire->Controls->Add(this->ReactiveDamage);
			this->FriendlyFire->Controls->Add(this->NormalDamage);
			this->FriendlyFire->Controls->Add(this->NoDamage);
			this->FriendlyFire->Location = System::Drawing::Point(56, 16);
			this->FriendlyFire->Name = S"FriendlyFire";
			this->FriendlyFire->Size = System::Drawing::Size(160, 104);
			this->FriendlyFire->TabIndex = 0;
			this->FriendlyFire->TabStop = false;
			this->FriendlyFire->Text = S"Friendly Fire Settings";
			// 
			// ReactiveDamage
			// 
			this->ReactiveDamage->Location = System::Drawing::Point(24, 72);
			this->ReactiveDamage->Name = S"ReactiveDamage";
			this->ReactiveDamage->Size = System::Drawing::Size(120, 24);
			this->ReactiveDamage->TabIndex = 2;
			this->ReactiveDamage->Text = S"Reactive damage";
			// 
			// NormalDamage
			// 
			this->NormalDamage->Location = System::Drawing::Point(24, 48);
			this->NormalDamage->Name = S"NormalDamage";
			this->NormalDamage->Size = System::Drawing::Size(120, 24);
			this->NormalDamage->TabIndex = 1;
			this->NormalDamage->Text = S"Normal damage";
			// 
			// NoDamage
			// 
			this->NoDamage->Checked = true;
			this->NoDamage->Location = System::Drawing::Point(24, 24);
			this->NoDamage->Name = S"NoDamage";
			this->NoDamage->Size = System::Drawing::Size(120, 24);
			this->NoDamage->TabIndex = 0;
			this->NoDamage->TabStop = true;
			this->NoDamage->Text = S"No damage";
			// 
			// CDialog
			// 
			this->CDialog->FullOpen = true;
			// 
			// SDialog
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(314, 336);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"SDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = S"LaserTanks Settings";
			this->tabControl->ResumeLayout(false);
			this->GameOptions->ResumeLayout(false);
			this->OtherSettings->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->HPRatio))->EndInit();
			this->AISettings->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->ChangeRate))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->Dispersion))->EndInit();
			this->GeneralSettings->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->CartridgeSize))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->ReloadTime))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->ShotDelay))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->MaxHP))->EndInit();
			this->Difficulty->ResumeLayout(false);
			this->GameControls->ResumeLayout(false);
			this->TeamSettings->ResumeLayout(false);
			this->FriendlyFire->ResumeLayout(false);
			this->ResumeLayout(false);

		}		
	public:	int SetDifficulty()
		{
			if (Easy->Checked)
				return 1;
			else if (Normal->Checked)
				return 2;
			else if (Hard->Checked)
				return 3;
			else
				return 4;
		}
	public: int SetFriendlyFire()
		{
			if (NoDamage->Checked)
				return 0;
			else if (NormalDamage->Checked)
				return 1;
			else
				return 2;
		}
	private: System::Void General_ValueChanged(System::Object *  sender, System::EventArgs *  e)
			 {
			 }

private: System::Void General_KeyPress(System::Object *  sender, System::Windows::Forms::KeyPressEventArgs *  e)
		 {
		 }

private: System::Void GameControls_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		 {
			 Pen * p = new Pen(Color::Black, 1);
			 SolidBrush * br = new SolidBrush(Color::Black);
			 KeyEventArgs * ka = new KeyEventArgs((Forms::Keys)0);
			 Object * ke;
			 StringFormat * sf = new StringFormat();
			 sf->Alignment = StringAlignment::Center;
			 sf->LineAlignment = StringAlignment::Center;
			 e->Graphics->Clear(GameControls->BackColor);
			 e->Graphics->DrawLine(p, 80, 0, 80, 300);
			 e->Graphics->DrawLine(p, 184, 0, 184, 300);
			 e->Graphics->DrawString("Player 1", this->Font, br, RectangleF(PointF(80,0), SizeF(104,26)), sf);
			 e->Graphics->DrawString("Player 2", this->Font, br, RectangleF(PointF(184,0), SizeF(104,26)), sf);
			 for (int i = 1; i < 10; i++)
			 {
				 // Order: ULDR - Stop - Rotate c'wise/a-c'wise - Fire - Pause
				 e->Graphics->DrawLine(p, 0, i*26, 288, i*26);
				 e->Graphics->DrawString(acs[i-1], this->Font, br, RectangleF(PointF(0,i*26), SizeF(80,26)), sf);
				 ka = new KeyEventArgs((Forms::Keys)kc[i-1,0]);
				 ke = __box(ka->KeyCode);
				 e->Graphics->DrawString(ke->ToString(), this->Font, br, RectangleF(PointF(80,i*26), SizeF(104,26)), sf);
				 ka = new KeyEventArgs((Forms::Keys)kc[i-1,1]);
				 ke = __box(ka->KeyCode);
				 e->Graphics->DrawString(ke->ToString(), this->Font, br, RectangleF(PointF(184,i*26), SizeF(104,26)), sf);
			 }
			 e->Graphics->DrawLine(p, 0, 260, 288, 260);
			 if (ci != -1)
			 {
				 RectangleF rf = RectangleF(ci*104 + 81, ri*26 + 27, 102, 24);
				 e->Graphics->FillRectangle(Brushes::White, rf);
				 e->Graphics->DrawString("Press a key...", this->Font, br, rf, sf);
			 }
		 }

private: System::Void DefaultP1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 kc[0,0] = Forms::Keys::Up;
			 kc[1,0] = Forms::Keys::Left;
			 kc[2,0] = Forms::Keys::Down;
			 kc[3,0] = Forms::Keys::Right;
			 kc[4,0] = Forms::Keys::NumPad0;
			 kc[5,0] = Forms::Keys::NumPad2;
			 kc[6,0] = Forms::Keys::NumPad1;
			 kc[7,0] = Forms::Keys::ControlKey;
			 kc[8,0] = Forms::Keys::P; 
			 GameControls_Paint(new Object(), new PaintEventArgs(GameControls->CreateGraphics(), ClientRectangle));
		 }

private: System::Void DefaultP2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 kc[0,1] = Forms::Keys::W;
			 kc[1,1] = Forms::Keys::A;
			 kc[2,1] = Forms::Keys::D;
			 kc[3,1] = Forms::Keys::S;
			 kc[4,1] = Forms::Keys::V;
			 kc[5,1] = Forms::Keys::H;
			 kc[6,1] = Forms::Keys::G;
			 kc[7,1] = Forms::Keys::Space;
			 kc[8,1] = Forms::Keys::F4;
			 GameControls_Paint(new Object(), new PaintEventArgs(GameControls->CreateGraphics(), ClientRectangle));
		 }

private: System::Void GameControls_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (tabControl->SelectedTab != GameControls)
				 return;
			 switch ((int)(e->X + 24)/104)
			 {
			 case 1:
				 ci = 0;
				 break;
			 case 2:
				 ci = 1;
				 break;
			 default:
				 ci = -1;
			 }
			 if (e->Y < 26 || e->Y > 260)
				 ci = -1;
			 ri = (int)e->Y/26 - 1;
			 GameControls_Paint(new Object(), new PaintEventArgs(GameControls->CreateGraphics(), ClientRectangle));
		 }

private: System::Void tabControl_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 ri = -1;
			 ci = -1;
			 if (tablock)
			 {
				 tabControl->SelectedTab = GameControls;
				 tablock = false;
			 }
		 }

private: System::Void tabControl_KeyDown(System::Object *  sender, System::Windows::Forms::KeyEventArgs *  e)
		 {
			 tablock = true;
			 if (ci == -1)
				 return;
			 for (int i = 0; i < 9; i++)
			 {
				 for (int j = 0; j < 2; j++)
				 {
					 if (i == ri && j == ci)
						 continue;
					 if (kc[i,j] == e->KeyValue)
						 return;
				 }
			 }
			 kc[ri,ci] = e->get_KeyValue(); // Without "get" this caused an internal compiler error...?
			 ci = -1;
			 GameControls_Paint(new Object(), new PaintEventArgs(GameControls->CreateGraphics(), ClientRectangle));
		 }

private: System::Void DefaultGeneral_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 for (int i = 0; i < GeneralSettings->Controls->Count; i++)
			 {
				 if (GeneralSettings->Controls->get_Item(i) != DefaultGeneral)
					 GeneralSettings->Controls->get_Item(i)->Enabled = !DefaultGeneral->Checked;
			 }
			 while (MaxHP->Value + ShotDelay->Value + ReloadTime->Value + CartridgeSize->Value != 216)
			 { // Okay... No idea why this doesn't work without the while. It only resolves once (checked)
				 MaxHP->set_Value(10);
				 ShotDelay->set_Value(50);
				 ReloadTime->set_Value(150);
				 CartridgeSize->set_Value(6);
			 }
		 }

private: System::Void DefaultAI_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 Dispersion->Value = 5;
			 ChangeRate->Value = 0.1;
		 }

private: System::Void Custom_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 AISettings->Enabled = true;
			 OtherSettings->Enabled = true;
		 }

private: System::Void Easy_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 Dispersion->Value = 8;
			 ChangeRate->Value = 0.08;
			 HPRatio->Value = 0.9;
			 Pickups->SelectedIndex = 0;
			 OtherSettings->Enabled = false;
			 AISettings->Enabled = false;
		 }

private: System::Void Normal_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 Dispersion->Value = 5;
			 ChangeRate->Value = 0.1;
			 HPRatio->Value = 1;
			 Pickups->SelectedIndex = 0;
			 OtherSettings->Enabled = false;
			 AISettings->Enabled = false;
		 }

private: System::Void Hard_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 Dispersion->Value = 3;
			 ChangeRate->Value = 0.14;
			 HPRatio->Value = 1.1;
			 Pickups->SelectedIndex = 0;
			 OtherSettings->Enabled = false;
			 AISettings->Enabled = false;
		 }

private: System::Void tabControl_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 tablock = false;
		 }

private: System::Void DefaultOther_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 HPRatio->Value = 1;
			 Pickups->SelectedIndex = 0;
		 }

private: System::Void T1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 T1->BackColor = Color::FromArgb(r->Next(0,256), r->Next(0,256), r->Next(0,256));
		 }

private: System::Void T1_DoubleClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 CDialog->Color = T1->BackColor;
			 if (CDialog->ShowDialog() == DialogResult::OK)
				 T1->BackColor = CDialog->Color;
		 }

private: System::Void T2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 T2->BackColor = Color::FromArgb(r->Next(0,256), r->Next(0,256), r->Next(0,256));
		 }

private: System::Void T2_DoubleClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 CDialog->Color = T2->BackColor;
			 if (CDialog->ShowDialog() == DialogResult::OK)
				 T2->BackColor = CDialog->Color;
		 }

private: System::Void T3_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 T3->BackColor = Color::FromArgb(r->Next(0,256), r->Next(0,256), r->Next(0,256));
		 }

private: System::Void T3_DoubleClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 CDialog->Color = T3->BackColor;
			 if (CDialog->ShowDialog() == DialogResult::OK)
				 T3->BackColor = CDialog->Color;
		 }

private: System::Void T4_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 T4->BackColor = Color::FromArgb(r->Next(0,256), r->Next(0,256), r->Next(0,256));
		 }

private: System::Void T4_DoubleClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 CDialog->Color = T4->BackColor;
			 if (CDialog->ShowDialog() == DialogResult::OK)
				 T4->BackColor = CDialog->Color;
		 }

};
}