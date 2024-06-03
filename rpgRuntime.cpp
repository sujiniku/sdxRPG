#include "DxLib.h"


#include <stdio.h> // �Z�[�u�p
#pragma warning(disable:4996) // fopen


#include <math.h>  // �؂�グ�v�Z�Ŏg�p

int zenkaiBcKasol_1[10];
int zenkaiBcKasol_2[10];


int koudouKiroku[10];
int koudouAtk = 0; int koudouMgk = 1;


int magicKiroku[10];
int sentouNaninme =0;


int magicAtkFlag[10] ;


int magicSel = 0;


int magicAtkDef[15] = {1000,100};

TCHAR magicList[15][30] = {
	{TEXT("�t�@�C�A")},
	{TEXT("�A�C�X")}
};

struct magic_def
{
	int def_id;
	TCHAR def_name[30];
	int power;
};

static struct magic_def magic_def_list[8];





int mapEneNum = 1;
int buyrange = 0;

int waitheal = 0; // �񕜂̕\�����̒���
int damepyon = 0; // �퓬���Ƀ_���[�W���s�����Ɠ������A��
int tekidame = 0; // �G�̃_���[�W�󂯂Ă�Ԃ����I��
int mikatadame = 0; // mikata�̃_���[�W�󂯂Ă�Ԃ����I��

int senkaFlag = 0;

// �E�B���h�E�F�̃f�t�H�l��萔���B�J�X�^���@�\������ꍇ�͕ʓr�ɐV���ȕϐ���p�ӂ���B
const int wind1R = 50;
const int wind1G = 50;
const int wind1B = 150;

const int window1color = GetColor(wind1R, wind1G, wind1B); // �E�B���h�E�̂ق��A�J�[�\���̃x�[�X�F�ł��g���\��������̂ŕϐ����B
void window1Draw(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		window1color, 1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255, 255, 255), 0);

}

const int darkwindow1color = GetColor(wind1R / 2, wind1G / 2, wind1B / 2);
void darkwindow1Draw(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		darkwindow1color, 1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255 / 2, 255 / 2, 255 / 2), 0);

}

int debugFlag = 0;

const int casolu1R = 250; // l �� 1 �̋�ʂ̂��� u �ǉ�
const int casolu1G = 150;
const int casolu1B = 150;

const int KasolColor = GetColor(casolu1R, casolu1G, casolu1B);
void redCasol1(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		KasolColor, 1);
}



int TimeKasolCount = 0;

void tenmetu(int X1, int Y1, int X2, int Y2) {

	double redVal = 0;

	double spanBlink = 120.0;

	if (TimeKasolCount < (int)spanBlink) {
		redVal = TimeKasolCount;
	}
	if (TimeKasolCount >= (int)spanBlink) {
		redVal = spanBlink * 2 - TimeKasolCount;
	}


	const int whiteMax = 180;

	DrawBox(X1, Y1, X2, Y2,

		GetColor(wind1R + (whiteMax - wind1R) * (redVal / spanBlink),
			wind1G + (whiteMax - wind1G) * (redVal / spanBlink),
			wind1B + 1 * (whiteMax - wind1B) * (redVal / spanBlink)),
		1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255, 255, 255), 0);


	TimeKasolCount = TimeKasolCount + 1;
	if (TimeKasolCount > spanBlink * 2) {
		TimeKasolCount = 0;
	}

}


void tenmetuStop(int X1, int Y1, int X2, int Y2) {

	double redVal = 0;

	double spanBlink = 120.0;

	if (TimeKasolCount < (int)spanBlink) {
		redVal = TimeKasolCount;
	}
	if (TimeKasolCount >= (int)spanBlink) {
		redVal = spanBlink * 2 - TimeKasolCount;
	}

	redVal = spanBlink / 2;

	const int whiteMax = 180;

	DrawBox(X1, Y1, X2, Y2,

		GetColor(wind1R + (whiteMax - wind1R) * (redVal / spanBlink),
			wind1G + (whiteMax - wind1G) * (redVal / spanBlink),
			wind1B + 1 * (whiteMax - wind1B) * (redVal / spanBlink)),
		1);


	if (TimeKasolCount > spanBlink * 2) {
		TimeKasolCount = 0;
	}

}



int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}


int jumpRyoku1 = 50;


static int selecting_mainmenu = 1;


int battlewait = 30;
//int battleTraFlag = 0;
int keyHaijyo = 0;

int monPosiX[5] = { 4,6 }; int monPosiY[5] = { 3,2 };
int monPosiX1 = 4; int monPosiY1 = 3; // �}�b�v��Ń����X�^�[�̂�����W
int monPosiX2 = 6; int monPosiY2 = 2;

int map1table[10][10] = {
	{ 1,1,1,1,1,1,1,1,1,1 }, //0 y
{ 1,0,0,0,0,0,0,0,0,1 }, //1
{ 1,0,0,0,0,0,0,0,0,1 }, //2
{ 1,0,0,0,0,0,0,0,0,1 }, //3
{ 1,0,0,0,0,0,0,0,0,1 }, //4
{ 1,0,0,0,0,0,0,0,0,1 }, //5
{ 1,1,1,1,1,1,0,0,1,1 }  //6
};





int maptreetable[20][20] = {
	{ 0,0,0,0,0,0,0,0,0,0 }, //0 y
{ 0,0,0,0,0,0,0,0,0,0 }, //1
{ 0,0,0,0,0,0,0,0,0,0 }, //2
{ 0,0,0,0,0,0,0,0,0,0 }, //3
{ 0,0,0,0,0,0,0,0,0,0 }, //4
{ 0,0,0,0,0,0,0,0,0,0 }, //5
{ 0,0,0,0,0,0,0,0,0,0 }  //6
};


int maptukotable[20][20] = {
	{ 0,0,0,0,0,0,0,0,0,0 }, //0 y
{ 0,0,0,0,0,0,0,0,0,0 }, //1
{ 0,0,0,0,0,0,0,0,0,0 }, //2
{ 0,0,0,0,0,0,0,0,0,0 }, //3
{ 0,0,0,0,0,0,0,0,0,0 }, //4
{ 0,0,0,0,0,0,0,0,0,0 }, //5
{ 0,0,0,0,0,0,0,0,0,0 }  //6
};



int maptreelayer[20][20] = {
	{ 0,0,0,0,0,0,0,0,0,0 }, //0 y
{ 0,0,0,0,0,0,0,0,0,0 }, //1
{ 0,0,0,0,0,0,0,0,0,0 }, //2
{ 0,0,0,0,0,0,0,0,0,0 }, //3
{ 0,0,0,0,0,0,0,0,0,0 }, //4
{ 0,0,0,0,0,0,0,0,0,0 }, //5
{ 0,0,0,0,0,0,0,0,0,0 }  //6
};





int x_mapDraw = 0;
int y_mapDraw = 0;

int hero1HPnow = 20;
int hero1HPmax = 50;


int hero2HPnow = 14;
int hero2HPmax = 30;


int toubouTyokugo1 = 0;
int toubouTyokugo[5] = { 0,0,0 };


int xPosi = 2;
int yPosi = 2;


int moving = 0; //�L�����`�b�v�摜���ړ����Ȃ�0

int keyEnableUp = 0;
int keyEnableDown = 0;
int keyEnableRight = 0;
int keyEnableLeft = 0;

int keyEnableUpRight = 0;

int keyEnableX = 0;
int keyEnableZ = 0;


const int waitTime1 = 40;
const int waitTime2 = 30;


int nyuuryokuMatiLR = waitTime1;
int nyuuryokuMatiUD = waitTime1;

int nyuuryokuMatiX = waitTime1;
int nyuuryokuMatiZ = waitTime1;


int nyuuryokuMatiUp = waitTime1;
int nyuuryokuMatiDown = waitTime1;


int nyuuryokuMatiRight = waitTime1;
int nyuuryokuMatiLeft = waitTime1;


int waitKasol = waitTime1;


int kasol2Target = 0;
int kasol3Target = 0;


int tempHandle;
int destMovable;


int shopMijissou = 1;

enum direction { upward, rightward, downward, leftward };
enum direction hero1_direction = downward;

enum mode {
	MODE_OP, MODE_LOAD, MODE_INITIAL, MODE_MAP,

	MODE_TOWN,

	MODE_Shop_Main, MODE_Shop_weapon_main, MODE_Shop_weapon_buy, MODE_Shop_weapon_sell, MODE_Shop_weapon_buyOld,
	MODE_Shop_armor_main, MODE_Shop_armor_buy, MODE_Shop_armor_sell, MODE_Shop_armor_buyOld,
	MODE_Shop_akusesari_main, MODE_Shop_item_main,





	MODE_MENU,

	MODE_narabikae_select1, MODE_narabikae_select2,

	MODE_ITEM_TYPE, MODE_ITEM_MENU, MODE_ITEM_MENU_FRONT,
	MODE_ITEMweapon_MENU, MODE_ITEMweapon_MENU_FRONT, MODE_ITEM_WHOM, MODE_ITEM_WHOM_FRONT,

	MODE_EQUIP_MAIN, MODE_EQUIP_EDIT, MODE_EQUIP_EDIT2,


	MODE_SAVE_MENU, MODE_saving_Now,

	MODE_BATTLE_COMMAND, MODE_BATTLE_COMMAND2, MODE_BATTLE_MAGIC,			
	MODE_BATTLE_NOW, MODE_BATTLE_WIN, BATTLE_Agility_proc,


	MODE_Guild_Main, MODE_Guild_Responce, MODE_Guild_Remove,

	itemModeMain, itemModeTarget, skillMode,
};
enum mode mode_scene = MODE_MAP;

// �c�[�����ǁA���؂߂�ǂ��̂Ŏc��
enum mode2 {
	MODE2_EQUIP_UnDef, // ����`�Ή�
	MODE2_EQUIP_HAND1,
	MODE2_EQUIP_SHIELD,
	MODE2_EQUIP_HELM,
	MODE2_EQUIP_ARMOR
};
enum mode2 mode2_scene = MODE2_EQUIP_HAND1;

int mode3_scene = 0;

//int itemkosuuyoki[10] = { 5,3,4 };
//int yakusouKosuu = 5;
//int dokukesiKosuu = 3;
//int soesiKosuu = 4;


int NaraSele1 = 0;

int NaraSele2 = 0;


int uketKyara = 1; // �퓬���ŁA���l�ڂ��_���[�W�󂯂Ă邩�B�u1�v��1�l�ځB

int pageSyori = 0;


// �A�C�e����ޔԍ�
const int itemOffset = 10;// 0�`9�Ԃ̓V�X�e�������p�Ɋm��
const int siyouType = itemOffset;  // =10

const int soubiOffset = 11; // wepoType�Ɠ��ԍ������A�g������ǐ����l���A�ʕϐ���p��

const int wepoType = soubiOffset; // 11
const int tateType = soubiOffset + 1; // 12;
const int kabutoType = soubiOffset + 2; // 13;

int PorEflag[20];

int tempPass = 0;


// ����͕������o�b�t�@�ȂǁB�i���[�h�ԍ��ł͂Ȃ��B�j
#define MAX_LOADSTRING 100
#define MAX_LENGTH 300 // �v�f���ɒ��� 


int afterShop = 0;

int shopAct = 0;

int sinamonoList = 0;

int popFlagTown = 0;
TCHAR popMsg[MAX_LENGTH] = TEXT("aaaa");


const int partymax = 3; // �{����4�����ǃe�X�g�̂���1���I��3
int whatuse = 0;

int beforeselect = 1; // �Ȃ�炩�̑I�����Œ��O�ɑI�񂾑I�����̔ԍ��B��ʍX�V�p�Ɏg���B

int whatedit1 = 0; // �����R�}���h�ȂǁA�ҏW�����邢�낢��ȍ�Ɨp
int whatedit2 = 0; // �ЂƂ̉�ʓ��ɁA�O��ʗp�J�[�\�����c���ꍇ�̏����ϐ�


int uwadumeFlag = 1; // 1�Ȃ��l�߂���B0�Ȃ�I�t�B�f�o�b�O���[�h�p // �o�O�b����0�ɖ߂�����

int akikosuu;
int akiHairetu[5];
int itemHairetu[50];
int itemTypeHairetu[50];


int event_tekiFast = 0;

int event_tekiSoutou = 0;

int uwagaki = 0;


int goukeiItem = 0;

int whomCHARA = 1;
int whomTargetID1 = 0;
int whomTargetID2 = 0;
int whomTargetID3 = 0;
int whomTargetID4 = 0;
int whomTargetID5 = 0;


int whomTargetID1party = 0;
int whomTargetID1hikae = 0;


int filterFlag = 0;

int FontYoffset = 30;

int idTemp = 0;
int battleID = 0;
int sentoKoudoCount = 0;
int timerFlag = 0;
int enemyAlldeadFlag = 0;// 0�Ȃ�A�G�͂܂��S�ł��ĂȂ��B1�œG���S�ŁB

int whoAction = 5; // 0 �Ȃ��l���̍U���B1�Ȃ�G�̍U���B����p�̂Ƃ肠�����̃t���O�B

int tourokuMapChip = 2;

int sankaAgility[BATTLE_Agility_proc]; // �f�����z��
int iremonoAgilityHairetu[BATTLE_Agility_proc]; // ���ꕨ���΂₳�z��
int actionOrder[BATTLE_Agility_proc]; // �s�����z��
int iremonoOrderHairetu[BATTLE_Agility_proc]; // ���ꕨ�����ǂ������z��
int mikataAgility[BATTLE_Agility_proc]; // �����̑���ł̑f�����z��B�u���ёւ��v�ő��񏇂��ς��̂ŁB
int tekiTairetuAgility[BATTLE_Agility_proc]; // �G�̑���ł̑f�����z��B�퓬���̃\�[�g�Ŏg���̂ŁB

// �����̍ގ�:

enum item_material
{
	mateWood,
	mateLether,
	mateCopper,
	mateBronze,

	mateIron,
	mateRichMetal,
	mateElse,
	mateNothing,
};


enum equip_type
{
	sword,
	spear,
	axe,
	crab,
	bow,
	rod,
	typeNothing,
	typeElse,

};


// �O���[�o���ϐ�:

int IsNewGame = 1; // ���߂Ă��̃Q�[�����N������Ƃ��A1�ł���B��x�ł��Z�[�u�����2�ɂȂ�B


int battleTimeFlag = 0; // �퓬���̃R�}���h�����̎����i�s�Ɏg�p�B1���Ǝ����i�s�B0�Œ�~�B

enum resource_embedded_flag { on, off };
enum resource_embedded_flag resource_embedded_var = off;


int makeNakamaNinzu = 5; // �v���O���}�[�̍�������ԃL�����̐l��
int tourokuNakama = 4 - 1; // ���ۂ̐l�����1���Ȃ� // �M���h�ɓo�^����Ă钇�Ԃ̐l���Ȃ̂ŕϐ�


int partyNinzuDone = 2, enemyNinzu = 1;
int partyNinzuTemp = partyNinzuDone;

int sankaNinzu = partyNinzuDone + enemyNinzu;


int hikaeNinzu = 2;


int partyNarabijyun[15] = { 0,1,-1,-1, -1 }; // �p�[�e�B����̕��ёւ��̏����Ɏg���\��
int partyNarabijyunBefore[15];
int partyNarabijyunAfter[15];



int hikaeNarabijyun[10] = { 2,3,-1, -1, -1 }; // �M���h�̏����Ɏg���\��

int monsterNarabijyun[5] = { 0,1,2,3,4 }; // �����X�^�[�̐퓬���̍s�����̏����Ɏg���\��



int guildResFlag = 0;

struct item_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int healti;
	int power;
	int item_type;
};


struct item_have
{
	int have_def_id;
	int have_kosuu;
};


struct weapon_have
{
	int have_def_id;
	int have_kosuu;
};



struct soubi_have
{
	int have_type;
	int have_def_id;
	int have_kosuu;
};


struct soubi_def
{
	int def_type;
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower[20];// �U���͂�h��͂ȂǂɎg�p


};



struct weapon_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// �U����


};


struct shield_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// �U����

};


struct shield_have
{
	int have_def_id;
	int have_kosuu;
};


struct helm_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// �U����

};


struct helm_have
{
	int have_def_id;
	int have_kosuu;
};


struct armor_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// �U����


};

struct armor_have
{
	int have_def_id;
	int have_kosuu;
};


int equipWeaponPower;

int bouguyaSina[10][10]; // 


struct monster_def
{
	int monster_id;
	TCHAR monster_name[MAX_LENGTH];
	int mon_hp_max;
	int mon_agility;

	int mon_attackPower;


	int mon_gold;
	int mon_exp;
};

int healflag = 0;
int healti = 0;
int healkioku = 0; // �񕜂������ƁA���b�̕\�����L�����邽�߁B


// �����p�[�e�B�\���� (�����X�^�[�\���̗̂��p)
struct heros_def
{
	int heros_id;
	TCHAR heros_name[MAX_LENGTH];
	int heros_hp;
	int heros_hpdiff;


	int heros_hp_max;
	int heros_agility;

	int heros_gold; // �E�B�U�[�h���B�݂����Ɋe�L�������ƂɃS�[���h�����Ă�悤�ɂȂ��Ă�B
	int heros_exp;

	int heros_HP0_flag;

	int PartyIn;

	int heroSoubi[20];
	int heroSoubiKasol[20];

	// �����i // �s�v
	int heros_weapon1;
	int heros_weapon2;
	int heros_shield;
	int heros_helm;
	int heros_yoroi;
	int heros_kote;
	int heros_sousyoku1;
	int heros_sousyoku2;
	int heros_sousyoku3;


	int heros_bukiKougekiRyoku;
	int heros_subiRyoku;

	int heros_para[20]; // �U���͂����̗͂p�����v20�A�p�ӁB

};

int kougekiPara = 1;
int syubiPara = 2;


enum next_attack_flag { next_is_hero, next_is_enemy };
enum next_attack_flag next_attack_var = next_is_hero;


static int encount_monsters_id = 2;


struct monsterTairetu_def
{
	int monsterTairetu[10];
};



static int selecting_item = 1;
static int selecting_item_x = 1;
static int selecting_item_y = 1;

static int selecting_itemBefore = 1;
static int selecting_itemAfter = 1;


// �퓬���Ɏg�p����ϐ��B �����X�^�[��`�Ƃ͕ʕ��B
static TCHAR monster_name[30];
static int monster_hp = 10;



static int enemy_alive[2] = { 1, 1 }; // 1�Ȃ琶���Ă�B0�Ȃ玀�S�B�Ƃ肠����2�C�Ԃ�
// �J�b�R���͓G�̔ԍ��B0�Ԃ��琔���Ă���B

static int encount_mons_alive = 1;


HINSTANCE hInst;                                // ���݂̃C���^�[�t�F�C�X
WCHAR szTitle[MAX_LOADSTRING];                  // �^�C�g�� �o�[�̃e�L�X�g
WCHAR szWindowClass[MAX_LOADSTRING];            // ���C�� �E�B���h�E �N���X��


TCHAR mojibuf[MAX_LENGTH] = TEXT("�͂��߂���");


// �������̋L�q�p�ɁA3��buf���m��
TCHAR mojibuf1[MAX_LENGTH] = TEXT("�͂��߂���");
TCHAR mojibuf2[MAX_LENGTH] = TEXT("�͂��߂���");
TCHAR mojibuf3[MAX_LENGTH] = TEXT("�͂��߂���");


void textFunc1(int x, int y) {
	DrawFormatString(x, y, GetColor(255, 255, 255), mojibuf);
}


#define GREEN 10,250,10
void textFuncHeal(int x, int y) {
	DrawFormatString(x, y, GetColor(GREEN), mojibuf);
}



static TCHAR filename_temp[100]; // �t�@�C���ǂݏ����Ŏg���ꎞ�I�ȃt�@�C����


static int mode2_mode_scene = 0;

static int selecting_OP = 1;

static int cursol_stop;
//static 
int your_money = 10000; // ����static �ɂ���ƁA�퓬�I����Ƀo�O��B



static TCHAR drawTalkString1[MAX_LENGTH] = TEXT("temp_talk1"); // ��b����1�s��
static TCHAR drawTalkString2[MAX_LENGTH] = TEXT("temp_talk2"); // ��b����2�s��
static TCHAR drawTalkString3[MAX_LENGTH] = TEXT("temp_talk3"); // ��b����3�s��


static int game_event1_end;
static int game_event2_end;

static int game_event1_end_dummuy;


static int key_remain = 1;


static int chara_x;
static int chara_y;

static int before_chara_x; // �ދp������1���O�ɖ߂�Ƃ��Ɏg���B
static int before_chara_y; //


static int start_x = 4;
static int start_y = 3;



// �}�b�v�̃T�C�Y�̕ϐ�
static int map_x_size = 10;
static int map_y_size = 7;


// �i�s��̕ǔ���̃A���S���Y���p�̕ϐ�
static int desti_x; // �i�s��(destination)�̕ǔ���̂��߂�x���W�ϐ� "desiti" means the destination.
static int desti_y; // �i�s��̕ǔ���̂��߂�x���W�ϐ�


// maptable �̏����� // ���g�͂Ƃ肠����0. ���S�̂��߁A�I�[�o�[�t���[���̉e����h���B
static int maptable[10][10] = {
	{ 0,0,0,0,0,0,0,0,0,0 }, //0 y
	{ 0,0,0,0,0,0,0,0,0,0 }, //1
	{ 0,0,0,0,0,0,0,0,0,0 }, //2
	{ 0,0,0,0,0,0,0,0,0,0 }, //3
	{ 0,0,0,0,0,0,0,0,0,0 }, //4
	{ 0,0,0,0,0,0,0,0,0,0 }, //5
	{ 0,0,0,0,0,0,0,0,0,0 }  //6
};


struct map_def
{
	int map_table[10][10];
	//int mapTransGoto[10][10][10];
};

static struct map_def map_def_list[8];


int MapTrans_position_x_map1to_map2 = 7;
int MapTrans_position_y_map1to_map2 = 6;


int town_X = 3;
int town_Y = 5;


static int MapTrans_position_x = MapTrans_position_x_map1to_map2;
static int MapTrans_position_y = MapTrans_position_y_map1to_map2;


struct MapTrans_def
{
	int MapTrans_id;

	int in_Where_Map;
	int to_Where_Map;

	int positionX; // ���̑J�ڂ̂���X���W
	int positionY;

	int chara_positionX; // �J�ڐ�}�b�v�ł̃L�����̊J�n���_�ł�X���W
	int chara_positionY;

};


// �}�b�v�J�ڗp�̍\���̕ϐ��̍쐬
static struct MapTrans_def MapTrans_def_list[8];


// map2 �̃f�[�^

int map2table[10][10] = {
	{ 1,1,0,1,0,0,0,0,0,1 }, //0 x
	{ 0,0,0,0,0,0,0,0,0,0 }, //1
	{ 0,0,0,0,0,0,0,0,0,0 }, //2
	{ 0,0,0,0,0,0,0,0,0,1 }, //3
	{ 0,0,0,0,0,0,0,0,0,0 }, //4
	{ 0,0,0,0,0,0,0,0,0,0 }, //5
	{ 0,1,1,1,1,1,0,0,1,0 }  //6
};


// int MapTrans_position_x_map2to_map1 = 2;
// int MapTrans_position_y_map2to_map1 = 0;


static int selecting_battle_mainmenu = 1;

static	int where_map = 1; // �ŏ��̃}�b�v

static int mapTrans_flag_is = 1;


// �����X�^�[�̈ʒu�B�Ƃ肠����2�C�Ԃ� // �Ȃ��t�B�[���h�}�b�v�ɂ���
static int positionX_enemy[5];
static int positionY_enemy[5];

int tekiSuu = 2; // �C�x���g�����p�ɁA���̃G���A�̓G�p�[�e�B�����Z�o�B
int gekiha_tekiSuu = 0;


static int TimeCount = 0; // ��Ɏ����i�s�i�G�̍s���Ȃǁj�Ɏg�p
static int keyCount = 0; // ��ɃL�[���͂̎��Ԑ����Ɏg�p




int dameKei = 0; // �_���[�W�v�Z��1�񐔂����s�����߂̃t���O


// �A�C�e�����j���[�ł̃J�[�\���ʒu�̌v�Z�p
void item_select() {

	if (selecting_item < 1 || goukeiItem == 0) {
		selecting_item = 1;
	}
	else if (selecting_item > goukeiItem) {
		selecting_item = goukeiItem;
	}

	selecting_item_x = ((selecting_item - 1) % 2) + 1;
	selecting_item_y = ((selecting_item - 1) / 2) + 1;


	// ���L�[�̓��͑O��ŃJ�[�\���������ʒu�̂܂܂�������A��ʂ��X�V���Ȃ����߂̏���
	selecting_itemAfter = selecting_item;


	// ���L�[�̓��͑O��ŃJ�[�\���������ʒu�̂܂܂�������A��ʂ��X�V���Ȃ�
	// ��ʂ̃`���c�L�h�~�̂���

	if (selecting_itemBefore != selecting_itemAfter) {
		//InvalidateRect(hWnd, NULL, FALSE);
		//UpdateWindow(hWnd);
	}
}


// �A�C�e�������̍\���̕ϐ��̍쐬
static struct item_def item_def_list[8]; // �A�C�e�������̍\���̔z��̐錾
static struct item_have item_have_list[8];


// �����i�̏����̍\���̔z��̍쐬

static struct weapon_def weapon_def_list[15]; // ���폈���̍\���̔z��̐錾
static struct weapon_have weapon_have_list[15];

static struct shield_def shield_def_list[15]; // �V�[���h�����̍\���̔z��̐錾
static struct shield_have shield_have_list[15];

static struct helm_def helm_def_list[15]; // �J�u�g�����̍\���̔z��̐錾
static struct helm_have helm_have_list[15];

static struct armor_def armor_def_list[15]; // �����C�����̍\���̔z��̐錾
static struct armor_have armor_have_list[15];


// �퓬�����p�̍\���̕ϐ��̍쐬
static struct monster_def monster_def_list[8];

static struct heros_def heros_def_list[8];


static struct monsterTairetu_def monsterTairetu_def_list[50];

int darkFlag = 0;


void menu_CharaSelectDraw() {

	// �摜�̓ǂݍ��݁uimage2�v�͕ϐ����B���ꂪ�w�i�t�B���^�[�B
	if (filterFlag == 0) {

		//Image image2(L"filter.png");

		// �摜�̕`��B �_�~�[�ϐ� graphics �𒇉�ĕ`�悷��K�v������.

		//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
		filterFlag = 1;
	}


	int winX1 = 10;
	int winY1 = 100;
	int winX2 = 300;
	int winY2 = 200;


	int StatsHPbaseX = winX1 + 120; int StatsHPbaseY = winY1 + 30;
	int offsetY = 120;


	for (int j = 0; j <= partyNinzuDone - 1; ++j) {

		// �w�i�̐�

		window1Draw(winX1, winY1 + offsetY * j,
			winX2, winY2 + offsetY * j);

		if (mode_scene == MODE_ITEM_WHOM) {
			// �J�[�\��
			if (whomTargetID1 == j) {

				tenmetu(winX1, winY1 + offsetY * (whomTargetID1),
					winX2, winY2 + offsetY * (whomTargetID1));

				//MessageBox(NULL, TEXT("�f�o�b�O�B"), TEXT("�e�X�g"), MB_OK);

			}
		}


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s fgh"), heros_def_list[partyNarabijyun[j]].heros_name);
		//DrawFormatString(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��
		textFunc1(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j);

		lstrcpy(mojibuf, TEXT("HP"));
		//DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��
		textFunc1(StatsHPbaseX, StatsHPbaseY + offsetY * j);


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_hp);
		// DrawFormatString(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��
		textFunc1(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j);


		int revwait = 120 - waitheal;

		if (healflag == 1 && healkioku == j) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j + 20 - 2 * revwait, GetColor(GREEN), mojibuf); // �݂ǂ�
			//textFuncHeal(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j + 20 - 2 * revwait);

		}

		if (healflag == 2 && healkioku == j) {

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j - (60) / 6, GetColor(GREEN), mojibuf); // �݂ǂ�
		   //textFuncHeal(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j - (60) / 6);
		}


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[partyNarabijyun[j]].heros_hp_max);
		//DrawFormatString(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��
		textFunc1(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j);

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
		//DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��
		textFunc1(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j);

		if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�퓬�s�\"));
			//DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��
			textFunc1(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j);

		}

	} // end for
}


void menu_CharaSelectDraw2() {


	// �摜�̓ǂݍ��݁uimage2�v�͕ϐ����B���ꂪ�w�i�t�B���^�[�B
	if (filterFlag == 0) {

		//Image image2(L"filter.png");

		// �摜�̕`��B �_�~�[�ϐ� graphics �𒇉�ĕ`�悷��K�v������.

		//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
		filterFlag = 1;
	}


	int shiftTemp = 140;

	int StatsHPbaseX = 130 + shiftTemp; int StatsHPbaseY = 130; // +100 ����
	int offsetY = 120;


	for (int j = 0; j <= partyNinzuDone - 1; ++j) {
		// �w�i�̐�

		window1Draw(10 + shiftTemp, 100 + offsetY * j, // +140
			300 + shiftTemp, 200 + offsetY * j);

		if (mode_scene == MODE_ITEM_WHOM) {
			// �J�[�\��
			if (whomTargetID1 == j) {

				tenmetu(10 + 10, 100 + 10 + 120 * (whomTargetID1),
					300 - 10, 100 + 70 + 120 * (whomTargetID1));

				//MessageBox(NULL, TEXT("�f�o�b�O�B"), TEXT("�e�X�g"), MB_OK);

			}
		}

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[partyNarabijyun[j]].heros_name);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		lstrcpy(mojibuf, TEXT("HP"));
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_hp);
		DrawFormatString(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[partyNarabijyun[j]].heros_hp_max);
		DrawFormatString(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


		if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�퓬�s�\"));
			DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		}

	}

}


// �퓬�ւ̓˓��̏��� // �̂��̃}�b�v����ŌĂт����̂ŁA�퓬�˓��ƃ}�b�v����̏����͌Œ�̂��ƁB
void battle_start() {

	// MessageBox(NULL, TEXT("battle_enemy_start�ɂ���B"), TEXT("�L�[�e�X�g"), MB_OK);

	// �ȉ��A��^��
	key_remain = 0;

	monster_hp = monster_def_list[encount_monsters_id - 1].mon_hp_max;

	_stprintf_s(monster_name, MAX_LENGTH, TEXT("%s"), monster_def_list[encount_monsters_id - 1].monster_name);
	tekiTairetuAgility[0] = monster_def_list[encount_monsters_id - 1].mon_agility;

	encount_mons_alive = 1;
	selecting_battle_mainmenu = 1;
	enemyAlldeadFlag = 0;

	selecting_mainmenu = 1;

	mode_scene = MODE_BATTLE_COMMAND;

}


// �����X�^�[�Ƃ̑�������
void check_encount_enemy(HWND hWnd) {

	if (where_map == 2) {
		for (int i = 0; i <= 1; i = i + 1)
		{
			if (enemy_alive[i] == 1) {
				if (chara_x == positionX_enemy[i] && chara_y == positionY_enemy[i]) {

					encount_monsters_id = i + 1;	// �����ɁA�N�Ƒ������������L�q

					// �X���C�� encount id �� 1��
					// �R�{���� id 2��

					battle_start();
				}
			}
		}
	}

}


void Akihaikeisan() {

	// int kousinNarabijyun[5];

	partyNinzuDone = partyNinzuTemp;


	int skip = 0;
	for (int temp = 0; temp < partymax; temp++)
	{
		if (partyNarabijyun[temp] >= 0) {

			// �킩��񂪁A���Ԃ�厖�Ȃ̂Ŏc��
			// kousinNarabijyun[temp - skip] = partyNarabijyun[temp];
		}

		if (partyNarabijyun[temp] < 0) {

			akiHairetu[skip] = temp;

			skip = skip + 1;
		}
	}

}


void hikaeKeisan() {
	// ���ꂪ�����
	int skip = 0; // remove ���߂ł�skip�𗬗p����B
	{
		for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {

			if (heros_def_list[temp].PartyIn == 0) {
				hikaeNarabijyun[skip] = temp;
				skip = skip + 1; // ������I����Ă���Askip�𑝂₷�B���̃����o�[�p�Ȃ̂ŁB
			}

			if (heros_def_list[temp].PartyIn == 1) {
				// �������Ȃ�
			}

		}

		hikaeNarabijyun[skip] = -1;
	}

}



void pre_guild() {

	//MessageBox(NULL, TEXT("�M���h�̃e�X�g���B\n"), TEXT("�L�[�e�X�g"), MB_OK);

	key_remain = 0;

	whomTargetID1 = 0; whomCHARA = 1;
	whomTargetID1party = 0; whomTargetID1hikae = 0;

	Akihaikeisan();


	// �T�������o�[�̔z�񏈗��̏���
	{
		if (uwadumeFlag == 1) {

			int skip = 0;
			for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {

				if (heros_def_list[temp].PartyIn == 0) {
					hikaeNarabijyun[skip] = temp;
					skip = skip + 1; // ������I����Ă���Askip�𑝂₷�B���̃����o�[�p�Ȃ̂ŁB
				}

				if (heros_def_list[temp].PartyIn == 1) {
					// �������Ȃ�
				}
			}
			hikaeNarabijyun[skip] = -1;
		}
	}
	mode_scene = MODE_Guild_Main;
}

int townFlag = 0; // ����Ȃ��ƁA�^�E������łĂ��A�^�E���ɓ��葱����

void check_encount_town() {


	//if (where_map == 1 && chara_x == town_X && chara_y == town_Y) {
	if (townFlag == 0 && where_map == 1 && xPosi == town_X && yPosi == town_Y) {

		// MessageBox(NULL, TEXT("kansu�̃e�X�g���B"), TEXT("�L�[�e�X�g"), MB_OK);

		popFlagTown = 1;
		lstrcpy(popMsg, TEXT("�p�[�e�B�̕Ґ����ł��܂��B"));

		mode_scene = MODE_TOWN;
		// pre_guild(); // �̂��̂��̃M���h�����̂��ߎc��

	}
}




void check_MapTransition() {
	//MessageBox(NULL, TEXT("�}�b�v�J�ڂ̔���ɂ���B"), TEXT("�L�[�e�X�g"), MB_OK);

	if (chara_x == MapTrans_def_list[(where_map)-1].positionX && chara_y == MapTrans_def_list[where_map - 1].positionY)
	{
		//MessageBox(NULL, TEXT("�}�b�v�J�ڂ̒��O�ɂ���B"), TEXT("�L�[�e�X�g"), MB_OK);		

		chara_x = MapTrans_def_list[where_map - 1].chara_positionX;
		chara_y = MapTrans_def_list[where_map - 1].chara_positionY;

		where_map = MapTrans_def_list[where_map - 1].to_Where_Map; // �}�b�v���ړ���ɏ㏑��

		// �g���̂��ߎc��
		//mapTrans_flag_is = 1; // �ړ���Ƀ}�b�v�J�ڂ����݂��邩


		desti_x = chara_x; // �ړ���̃��Z�b�g		
		desti_y = chara_y;


		// ���������A�ړ���̃}�b�v�`��̂��߂̏���

		// �ړ���}�b�v�ɂ���}�b�v�J�ڂ̏�������
		MapTrans_position_x = MapTrans_def_list[where_map - 1].positionX;
		MapTrans_position_y = MapTrans_def_list[where_map - 1].positionY;


		// maptable�Ɉړ���}�b�v����
		int x_map = 0, y_map = 0;

		for (x_map = 0; x_map <= 9; ++x_map)
		{
			for (y_map = 0; y_map <= 6; ++y_map)
			{
				// ������e�́A�ړ���}�b�v�̑�������邱�Ƃɒ���

				for (int i = 0; i <= tourokuMapChip - 1; ++i) { // �S�}�b�v���`�F�b�N
					if (where_map == i + 1) {
						maptable[y_map][x_map] = map_def_list[i].map_table[y_map][x_map];
					}
				}

			}
		} // for 
	}
}


static int hero1_already_attack_flag = 0;
static int enemy_already_attack_flag = 0;

static int battle_key = 1;

static int damage_HeroAttack = 1;
static int damage_EnemyAttack = 0;


void heroside_attack() {
	tekidame = 1;
	damepyon = 0;

	int pnCommon = partyNarabijyun[actionOrder[sentoKoudoCount]];

	if (heros_def_list[pnCommon].heros_HP0_flag == 0) {
		// ��l�������̍U��

		/* �����̎� */
		// wWinMain �Œ�`�ς�

		/* �T�C�R�� */

		// koudouKiroku[sentouNaninme] = koudouMgk;

		if(koudouKiroku[pnCommon] == koudouAtk) {
			damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_para[kougekiPara];	
		}

		if (koudouKiroku[pnCommon] == koudouMgk) {
				damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_para[kougekiPara] + magic_def_list[magicKiroku[pnCommon]].power ;
		}

		// 
		// 
		// �G�Ƀ_���[�W
		monster_hp = monster_hp - damage_HeroAttack;

		// �����X�^�[�̎��S�̏���
		if (monster_hp < 1) {
			monster_hp = 0;

			enemy_alive[(encount_monsters_id)-1] = 0; // �t�B�[���h��̓G�̏���

			encount_mons_alive = 0; // ���ݐ퓬���̓G�����S�Ƀt���O�ݒ�

		}
	}
}


void enemy_attack() {
	tekidame = 0;
	damepyon = 0;

	// �G�����̍U��
	/* �����̎� */
		// wWinMain �Œ�`�ς�

	int pnCommon = partyNarabijyun[actionOrder[sentoKoudoCount]];

	// �_���[�W�v�Z��
	/* �T�C�R�� */
		damage_EnemyAttack = rand() % (6 / 2) + 10 + 2 * monster_def_list[encount_monsters_id - 1].mon_attackPower
			- heros_def_list[partyNarabijyun[0]].heros_para[syubiPara];


	if (damage_EnemyAttack <= 0) {
		damage_EnemyAttack = 0;
	}

	// ����1�l�ڂɃ_���[�W
	if (heros_def_list[partyNarabijyun[0]].heros_HP0_flag != 1) {

		heros_def_list[partyNarabijyun[0]].heros_hp = heros_def_list[partyNarabijyun[0]].heros_hp - damage_EnemyAttack;
		uketKyara = 1;
	}

	if (heros_def_list[partyNarabijyun[0]].heros_HP0_flag == 1 && partyNinzuDone >= 2) {

		heros_def_list[partyNarabijyun[1]].heros_hp = heros_def_list[partyNarabijyun[1]].heros_hp - damage_EnemyAttack;
		uketKyara = 2;
	}

	if (heros_def_list[partyNarabijyun[0]].heros_HP0_flag == 1
		&& partyNinzuDone >= 3
		&& heros_def_list[partyNarabijyun[1]].heros_HP0_flag == 1) {

		heros_def_list[partyNarabijyun[2]].heros_hp = heros_def_list[partyNarabijyun[2]].heros_hp - damage_EnemyAttack;
		uketKyara = 3;
	}

	int tempVal;
	for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
		// MessageBox(NULL, TEXT("����fo�����B"), TEXT("�L�[�e�X�g"), MB_OK);
		tempVal = partyNarabijyun[temp];

		if (heros_def_list[tempVal].heros_hp < 1) {
			heros_def_list[tempVal].heros_hp = 0;

			// �퓬�s�\�t���O���I��
			heros_def_list[tempVal].heros_HP0_flag = 1;
		}
	}
	// MessageBox(NULL, TEXT("���܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

}





void hikaesai() {
	filterFlag = 1;
	// Draw_map(hdc); // ���}���u�B�ł���΁Ahbitmapu���O���[�o���ϐ��ɂ��������A���@��������Ȃ��B
	// �����������x�ɖ�肪������悤�Ȃ�A�w�i�F���i�}�b�v�w�i�`�����߂āj���ɕύX�B


	//Draw_map(hdc);




	int offsetYtemp1 = 100;
	//SelectObject(hdc, blue_thin_1);

	if (mode_scene != MODE_Guild_Main) {
		// BrushDarkBlue_set(hdc);
		darkwindow1Draw(10, offsetYtemp1,
			offsetYtemp1 + 100, 400);
	}

	if (mode_scene == MODE_Guild_Main) {
		// BrushDarkBlue_set(hdc);
		window1Draw(10, offsetYtemp1,
			offsetYtemp1 + 100, 400);
	}


	// Rectangle(hdc, 10, offsetYtemp1,		offsetYtemp1 + 100, 400);



	int carsoruHigh = 50; // �����X�p���ƃJ�[�\�������͓����ɂ��邱��

	//BrushPink_set(hdc);

	if (mode_scene != MODE_Guild_Main) {
		//BrushDarkPink_set(hdc);
		tenmetuStop(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1hikae),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1hikae)); // ���ƂŃ_�[�N��

	}

	if (mode_scene == MODE_Guild_Main) {
		tenmetu(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1hikae),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1hikae));

	}



	int offsetXtemp1 = 30; // �J�[�\�������Ɠ����Ȃ̂͋��R�B
	int yspan1 = carsoruHigh;

	window1Draw(offsetXtemp1 - 1 * 10, offsetYtemp1 - 20, offsetXtemp1 + 150, offsetYtemp1 + 10);
	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�T�������o�["));

	// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), GetColor(255, 255, 255), mojibuf); // ������`�悷��


	if (uwadumeFlag == 0) {
		for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {
			if (heros_def_list[temp].PartyIn == 0) {
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[temp].heros_name);
			}

			if (heros_def_list[temp].PartyIn == 1) {
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�o����: %s"), heros_def_list[temp].heros_name);
			}

			// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, mojibuf, lstrlen(mojibuf));

			DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, GetColor(255, 255, 255), mojibuf); // ������`�悷��


		}


		// temp == tourokuNakama + 1    �ɑ���
		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�y�O���z"));
		// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120, mojibuf, lstrlen(mojibuf));

		DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120, GetColor(255, 255, 255), mojibuf); // ������`�悷��


	}


	if (uwadumeFlag == 1) {

		int skip = 0;

		// �T���I���L���� -1 �܂œǂݍ���ł�̂ŁA�ǂݍ��݉񐔂͍T���l������1�񑽂�
		for (int temp = 0; temp <= hikaeNinzu; temp = temp + 1) { // temp��0���琔���Ă�̂ŁA2���ڂ� hikaeNinzu;
		// for (int temp = 0; temp <= 1; temp = temp + 1) { // 2���ڂ� hikaeNinzu;

			if (hikaeNarabijyun[temp] > -1) { // �E�ӂ�0���Ǝ�l������\���ɂȂ��Ă��܂�

				if (heros_def_list[hikaeNarabijyun[temp]].PartyIn == 0) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s "), heros_def_list[hikaeNarabijyun[temp]].heros_name);
					skip = skip + 1;
				}

				if (heros_def_list[hikaeNarabijyun[temp]].PartyIn == 1) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�Ґ���: %s"), heros_def_list[hikaeNarabijyun[temp]].heros_name);
				} // �f�o�b�O�p�Ƀ��b�Z�[�W���u�Ґ��v�ɕς��Ă�B

				// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, mojibuf, lstrlen(mojibuf));

				DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, GetColor(255, 255, 255), mojibuf); // ������`�悷��




			}

		}


		// temp == tourokuNakama + 1    �ɑ���
		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�y�O���z"));
		// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (skip)+120, mojibuf, lstrlen(mojibuf));

		DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (skip)+120, GetColor(255, 255, 255), mojibuf); // ������`�悷��

	}

	// �f�o�b�O��
	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Hikae[0]: %d"), hikaeNarabijyun[0]);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50, mojibuf, lstrlen(mojibuf));


	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Hikae[1]: %d"), hikaeNarabijyun[1]);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 1, mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 1, GetColor(255, 255, 255), mojibuf); // ������`�悷��


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�T���l��: %d"), hikaeNinzu);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 2, mojibuf, lstrlen(mojibuf));


	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��



	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("whomCH: %d"), whomCHARA);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 3, mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("P�l��: %d"), partyNinzuTemp);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 4, mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 4, GetColor(255, 255, 255), mojibuf); // ������`�悷��

}



void parsai() {

	// �p�[�e�B�����o�[�����ĕ`��̕K�v����

	//BrushBlue_set(hdc);
	// Rectangle(hdc, 10, 10, 610, 80);

	//BrushPink_set(hdc);


	int offsetXtemp2 = 220; int offsetYtemp2 = 100;
	//SelectObject(hdc, blue_thin_1);
	// Rectangle(hdc, offsetXtemp2, offsetYtemp2,	offsetXtemp2 + 200, offsetYtemp2 + 300);

	window1Draw(offsetXtemp2, offsetYtemp2, offsetXtemp2 + 200, offsetYtemp2 + 300);

	int kasoruHeight = 50;
	//BrushPink_set(hdc);

	if (mode_scene == MODE_Guild_Main) {
		//BrushDarkPink_set(hdc);
		// �悭�������̂ŁA�e�X�g�Ŋm�F
	}

	if (mode_scene == MODE_Guild_Remove) {
		//Rectangle(hdc, offsetXtemp2 + 10, offsetYtemp2 + 10 + 60 * (whomTargetID1party),offsetXtemp2 + 150, offsetYtemp2 + kasoruHeight + 10 + 60 * (whomTargetID1party));

		tenmetu(offsetXtemp2 + 10, offsetYtemp2 + 10 + 60 * (whomTargetID1party), offsetXtemp2 + 150, offsetYtemp2 + kasoruHeight + 10 + 60 * (whomTargetID1party));

	}

	int yspan1 = 50;


	window1Draw(offsetXtemp2 + 10, offsetYtemp2 - 20, offsetXtemp2 + 180, offsetYtemp2 + 10);
	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�p�[�e�B�����o�["));

	// TextOut(hdc, offsetXtemp2 + 30, -10 + offsetYtemp2 + yspan1 * (0), mojibuf, lstrlen(mojibuf));
	DrawFormatString(offsetXtemp2 + 30, -10 + offsetYtemp2 + yspan1 * (0), GetColor(255, 255, 255), mojibuf); // ������`�悷��





	for (int temp = 0; temp <= partymax - 1; temp = temp + 1) {

		if (partyNarabijyun[temp] >= 0) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[partyNarabijyun[temp]].heros_name);
		}

		if (partyNarabijyun[temp] < 0) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�y�󂫘g�z"));
		}

		//TextOut(hdc, offsetXtemp2 + 30, offsetYtemp2 + 30 + yspan1 * (temp), mojibuf, lstrlen(mojibuf));

		DrawFormatString(offsetXtemp2 + 30, offsetYtemp2 + 30 + yspan1 * (temp), GetColor(255, 255, 255), mojibuf); // ������`�悷��

	}

	// �����p aaaaaaaaaaaaa

}




char strCount[64];


void keyEnableReset() {

	keyEnableZ = 0;
	keyEnableX = 0;

	keyEnableUp = 0;
	keyEnableDown = 0;

	nyuuryokuMatiZ = waitTime1;
	nyuuryokuMatiX = waitTime1;

	nyuuryokuMatiUp = waitTime1 / 2;
	nyuuryokuMatiDown = waitTime1 / 2;

}


int toubouSeikou = 0;


struct tykou {
	struct soubi_def Stype[20];
};

static struct tykou soubihin[20]; // �\���̔z��̐錾
static struct tykou* Asoubuhin = &soubihin[20];



struct tykou2 {
	struct soubi_have Stype[10];
};

struct tykou2 soubiSyoji[20]; // �\���̔z��̐錾

static struct tykou2* AsoubuSyoji = &soubiSyoji[10];


void itemList(struct tykou soubuhin[10], struct tykou2 soubiSyoji[20], int kasolFlag) {

	// darkFlag = 1;
	darkFlag = 0;

	window1Draw(10, 100, 600, 400);

	// �J�[�\���`��ݒ�
	int spanY = FontYoffset;
	int Y0 = 120;

	// �������͔`�����Ȃ̂ŃJ�[�\���̓I�t��


	if (kasolFlag == 1) {
		tenmetu(20 + (selecting_item_x - 1) * 300, Y0 + (selecting_item_y - 1) * spanY, 250 + (selecting_item_x - 1) * 300, Y0 + spanY + (selecting_item_y - 1) * spanY);
	}

	goukeiItem = 0;

	int column = 2;

	int xcommon;
	int ycommon;

	// �\���t���O
	int ViewFlag[10]; // 0�̓V�X�e���p, 1���g�p�i, 2������A3���^�e�A4���J�u�g

	// int ViewFlagItem = 1;
	// int ViewFlagWeapon = 0;
	// int ViewFlagShield = 0;
	// int ViewFlagHelm = 0;

	if (mode_scene == MODE_ITEMweapon_MENU || mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEM_TYPE) {

		// ���S�̂��߈�U0��

		for (int temp = 1; temp <= 4; temp = temp + 1) {
			ViewFlag[temp] = 0;

		}

		/*
		ViewFlag[1] = 0;  // ViewFlagItem = 0;
		ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
		ViewFlag[3] = 0;  // ViewFlagShield = 0;
		ViewFlag[4] = 0;  // ViewFlagHelm = 0;
		*/


		// �\���t���O�ݒ�
		if (mode_scene == MODE_ITEM_MENU || (selecting_mainmenu == 1 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 1;  // ViewFlagItem = 1;

			for (int temp = 2; temp <= 4; temp = temp + 1) {
				ViewFlag[temp] = 0; // �����i�͕\���I�t

			}

			//ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
			//ViewFlag[3] = 0;  // ViewFlagShield = 0;
			//ViewFlag[4] = 0;  // ViewFlagHelm = 0;
		}

		if (mode_scene == MODE_ITEMweapon_MENU || (selecting_mainmenu == 2 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;  // ViewFlagItem = 0;


			for (int temp = 2; temp <= 4; temp = temp + 1) {
				ViewFlag[temp] = 1; // �����i�͕\���I��

			}
			//ViewFlag[2] = 1;  // ViewFlagWeapon = 1;
			//ViewFlag[3] = 1;  // ViewFlagShield = 1;
			//ViewFlag[4] = 1;  // ViewFlagHelm = 1;
		}

		if ((selecting_mainmenu == 3 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;   //ViewFlagItem = 0;

			for (int temp = 2; temp <= 4; temp = temp + 1) {
				ViewFlag[temp] = 0; // �����i�͕\���I�t

			}

			//ViewFlag[2] = 0;   //ViewFlagWeapon = 0;
			//ViewFlag[3] = 0;   //ViewFlagShield = 0;
			//ViewFlag[4] = 0;   //ViewFlagHelm = 0;
		}

	}

	int LimintTemp = goukeiItem;
	goukeiItem = 0;


	// �A�C�e���z��̃N���A�B�O�̎c�[���c��ꍇ������̂ŁB
	itemHairetu[0] = -99;


	int itemIDcount = 0; // for���̊O�Ŏg���̂ŁA��������_��

	// �g�p�i�̔z����
	if (ViewFlag[1]) {

		LimintTemp = goukeiItem;

		for (idTemp = 1; idTemp <= 3; idTemp = idTemp + 1)
		{

			if (item_have_list[idTemp].have_kosuu != 0) {

				goukeiItem = goukeiItem + 1;

				{
					itemHairetu[itemIDcount] = idTemp;
					itemTypeHairetu[itemIDcount] = siyouType;
					itemIDcount = itemIDcount + 1;
				}
			}
		} // �g�p�i�̔z����
	}

	// 
	for (int tempVal1 = 2; tempVal1 <= 4; tempVal1 = tempVal1 + 1) {

		if (ViewFlag[tempVal1]) {

			LimintTemp = goukeiItem;

			// �����i�̔z����
			for (idTemp = 1; idTemp <= 2; idTemp = idTemp + 1)
			{

				int	localSouType = soubiOffset + tempVal1 - 2;
				if ((soubiSyoji[idTemp].Stype[localSouType]).have_kosuu != 0) {


					goukeiItem = goukeiItem + 1;

					{
						itemHairetu[itemIDcount] = idTemp;
						itemTypeHairetu[itemIDcount] = localSouType;
						itemIDcount = itemIDcount + 1;
					}
				}
			} // �����i�̔z����
		}

	}

	itemTypeHairetu[itemIDcount] = -99; // �I�����Ӗ����鐔�B

	// ����R�}���h�̓���\���═��\���Ȃ�
	{
		for (int temp = 0; temp <= 10; temp = temp + 1) {

			int temp2 = temp + pageSyori * 6;

			if (itemTypeHairetu[temp2] == -99) {
				lstrcpy(mojibuf, TEXT("   "));

				DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��
				break;
			}

			xcommon = 30 + 300 * floor((temp) % column);
			ycommon = 130 + spanY * floor((temp) / column);

			if (itemTypeHairetu[temp2] == siyouType) {
				lstrcpy(mojibuf, item_def_list[itemHairetu[temp2]].def_name);
			}


			int defSoubiType = 2; // ��`���I����������i�̎�ސ�����}�C�i�X1�B ���Ƃ��Ε���A�J�e�A�J�u�g�Ȃ� 3-1=2

			if (itemTypeHairetu[temp2] >= soubiOffset // wepoType
				&& itemTypeHairetu[temp2] <= soubiOffset + defSoubiType // kabutoType
				)
				/* // �Ӗ�
				if (itemTypeHairetu[temp2] == soubiOffset // wepoType
				|| itemTypeHairetu[temp2] == soubiOffset +1 // tateType
				|| itemTypeHairetu[temp2] == soubiOffset + 2 // kabutoType
				)
				*/
			{

				int locType;

				locType = itemTypeHairetu[temp2];// �Ӗ��͉��L�R�����g�̓��e	

				/*		// ���̃R�����g�͏�L�̐����Ȃ̂ŏ�����
				if (itemTypeHairetu[temp2] == wepoType) {
					locType = wepoType;

				}
				if (itemTypeHairetu[temp2] == tateType) {
					locType = tateType;
				}
				if (itemTypeHairetu[temp2] == kabutoType) {
					locType = kabutoType;
				}
				*/

				// �����i�̖��O�\���Z�b�g. �܂����͕\�����ĂȂ�
				lstrcpy(mojibuf, (soubihin[itemHairetu[temp2]].Stype[locType]).def_name);

			}

			DrawFormatString(xcommon, ycommon, GetColor(255, 255, 255), mojibuf);

			// ���Z�b�g�̃��W���[��
			// �����̔w�i�N���A�p
			lstrcpy(mojibuf, TEXT("   "));
			DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf);


			if (itemTypeHairetu[temp2] == siyouType) {
				// ����̌��\��. �\���͌㏈����DrawFormat �ňꊇ
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), item_have_list[itemHairetu[temp2]].have_kosuu);
			}

			int locType = itemTypeHairetu[temp2];

			//if (itemTypeHairetu[temp2] == wepoType || itemTypeHairetu[temp2] == tateType
			//	|| itemTypeHairetu[temp2] == kabutoType
			//	)

			if (itemTypeHairetu[temp2] >= soubiOffset // wepoType				
				&& itemTypeHairetu[temp2] <= soubiOffset + defSoubiType // kabutoType				
				)
			{
				// �����i�̌��\��. �\���͌㏈����DrawFormat �ňꊇ
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[itemHairetu[temp2]].Stype[locType]).have_kosuu);
			}

			// ��L��������ۂɕ\������
			DrawFormatString(xcommon + 130, ycommon, GetColor(255, 255, 255), mojibuf);

		}
	} // ����R�}���h�̓���\���═��\���Ȃ�

	itemIDcount = 0;
} // itemlist



bool CheckZetc = CheckHitKey(KEY_INPUT_Z) == 1 && keyEnableZ == 1 && nyuuryokuMatiZ <= 0; // if���Ŏg��

void CheckZetcFunc(void) {
	CheckZetc = CheckHitKey(KEY_INPUT_Z) == 1 && keyEnableZ == 1 && nyuuryokuMatiZ <= 0; // ����͍X�V�p

}

bool CheckXetc = CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1 && nyuuryokuMatiX <= 0; // if���Ŏg��
void CheckXetcFunc(void) {
	CheckXetc = CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1 && nyuuryokuMatiX <= 0; // ����͍X�V�p

}

bool CheckUPetc = CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp != 1 && nyuuryokuMatiUp <= 0; // if���Ŏg��
void CheckUPetcFunc(void) {
	CheckUPetc = CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && nyuuryokuMatiUp <= 0; // ����͍X�V�p

}

void endUP() {

	keyEnableUp = 0;
	nyuuryokuMatiUp = waitTime1;
	keyEnableReset();
}

void endUP2() {

	keyEnableUp = 0;
	nyuuryokuMatiUp = waitTime1;
	// keyEnableReset();
}



void endZ() {

	keyEnableZ = 0;
	nyuuryokuMatiZ = waitTime1;
	keyEnableReset();
}

void endX() {

	keyEnableX = 0;
	nyuuryokuMatiX = waitTime1;
	keyEnableReset();
}



void endZ2() {

	keyEnableZ = 0;
	nyuuryokuMatiZ = waitTime1;
	//keyEnableReset();
}

void endX2() {

	keyEnableX = 0;
	nyuuryokuMatiX = waitTime1;
	//keyEnableReset();
}



bool CheckDOWNetc = CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1 && nyuuryokuMatiDown <= 0;
void CheckDOWNetcFunc(void) {
	CheckDOWNetc = CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1 && nyuuryokuMatiDown <= 0;

}

void endDOWN() {

	keyEnableDown = 0;
	nyuuryokuMatiDown = waitTime1;
	keyEnableReset();
}

void endDOWN2() {

	keyEnableDown = 0;
	nyuuryokuMatiDown = waitTime1;
	//keyEnableReset();
}

struct sinaList {
	int Grouptype;
	int subID;
};

// static 
struct sinaList hinmoku[5]; // �\���̔z��̐錾

int koumoku_Y = 200;
int kasolOffsetY = 30;

void hinmokuView() {


	int stypeOffset = soubiOffset - 1; //10;
	int afterOffTemp = stypeOffset + 1;


	for (int temp = 0; temp <= 5; temp = temp + 1) {

		if (hinmoku[temp].Grouptype == -99) {
			buyrange = temp - 1;
			break;
		}

		lstrcpy(mojibuf, soubihin[hinmoku[temp].subID].Stype[hinmoku[temp].Grouptype].def_name);

		// TextOut(hdc, 280, koumoku_Y + 30 + 30 * temp, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280, koumoku_Y + 30 + 30 * temp, GetColor(255, 255, 255), mojibuf); // ������`�悷��


		lstrcpy(mojibuf, TEXT("50G"));
		// TextOut(hdc, 280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, mojibuf, lstrlen(mojibuf));

		DrawFormatString(280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, GetColor(255, 255, 255), mojibuf); // ������`�悷��



		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[hinmoku[temp].subID].Stype[hinmoku[temp].Grouptype]).have_kosuu);

		DrawFormatString(280 + 100 * 2 + 50, koumoku_Y + 30 + kasolOffsetY * temp, GetColor(255, 255, 255), mojibuf); // ������`�悷��




	} // for temp �I���

	if (shopMijissou == 1) {

		int temp = 1;

		lstrcpy(mojibuf, TEXT("������"));
		// TextOut(hdc, 280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, mojibuf, lstrlen(mojibuf));

		DrawFormatString(280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, GetColor(255, 255, 255), mojibuf); // ������`�悷��



	}








}






int offsetYtemp1 = 100;


void shopCommon1() {


	int offsetYtemp1 = 100;
	// SelectObject(hdc, blue_thin_1);

	// Rectangle(hdc, 10, offsetYtemp1, offsetYtemp1 + 100, 400);

	window1Draw(10, offsetYtemp1, offsetYtemp1 + 100, 400);


	int carsoruHigh = 50; // �����X�p���ƃJ�[�\�������͓����ɂ��邱��

	// BrushDarkPink_set(hdc);

	if (mode_scene == MODE_Shop_Main || mode_scene == MODE_Shop_weapon_main || mode_scene == MODE_Shop_armor_main) {
		tenmetu(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1)); // 
	}
	else {
		tenmetuStop(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1)); // ���ƂŃ_�[�N�ɒ���
	}




	int offsetXtemp1 = 30; // �J�[�\�������Ɠ����Ȃ̂͋��R�B
	int yspan1 = carsoruHigh;


	window1Draw(offsetXtemp1 - 20, offsetYtemp1 - 20, offsetXtemp1 + 70, offsetYtemp1 + 20);

	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�s����"));
	// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), GetColor(255, 255, 255), mojibuf); // ������`�悷��


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("����"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (1), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (1), GetColor(255, 255, 255), mojibuf); // ������`�悷��


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�h��"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (2), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (2), GetColor(255, 255, 255), mojibuf); // ������`�悷��


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�����i"));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (3), GetColor(255, 255, 255), mojibuf); // ������`�悷��


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("����"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (4), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (4), GetColor(255, 255, 255), mojibuf); // ������`�悷��



	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�o��"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (5), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (5), GetColor(255, 255, 255), mojibuf); // ������`�悷��

}

int whomtargetID2;

void shopCommand() {

	//lstrcpy(mojibuf, TEXT("���퉮�e�X�g����B"));
	//TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

	//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


	//SelectObject(hdc, blue_thin_1);
	window1Draw(250, 100,
		480, 150);


	int BuySellX = 280;
	int BuySellY = 120;

	int carsoruHigh = 30;
	int spanX = 50;


	//1; // �u����v�ɃJ�[�\��

	//BrushDarkPink_set(hdc);

	if (mode_scene == MODE_Shop_Main || mode_scene == MODE_Shop_weapon_main || mode_scene == MODE_Shop_armor_main) {
		tenmetu(BuySellX + spanX * (shopAct), offsetYtemp1 + 10,
			BuySellX + 40 + spanX * (shopAct), offsetYtemp1 + 60); // 
	}
	else {
		tenmetuStop(BuySellX + spanX * (shopAct), offsetYtemp1 + 10,
			BuySellX + 40 + spanX * (shopAct), offsetYtemp1 + 60); // ���ƂŃ_�[�N��
	}



	lstrcpy(mojibuf, TEXT("����"));
	// TextOut(hdc, BuySellX, BuySellY, mojibuf, lstrlen(mojibuf));

	DrawFormatString(BuySellX, BuySellY, GetColor(255, 255, 255), mojibuf); // ������`�悷��


	lstrcpy(mojibuf, TEXT("����"));
	//TextOut(hdc, BuySellX + spanX * 1, BuySellY, mojibuf, lstrlen(mojibuf));


	DrawFormatString(BuySellX + spanX * 1, BuySellY, GetColor(255, 255, 255), mojibuf); // ������`�悷��


	lstrcpy(mojibuf, TEXT("����"));
	// TextOut(hdc, BuySellX + spanX * 2, BuySellY, mojibuf, lstrlen(mojibuf));

	DrawFormatString(BuySellX + spanX * 2, BuySellY, GetColor(255, 255, 255), mojibuf); // ������`�悷��



	lstrcpy(mojibuf, TEXT("�o��"));
	// TextOut(hdc, BuySellX + spanX * 3, BuySellY, mojibuf, lstrlen(mojibuf));

	DrawFormatString(BuySellX + spanX * 3, BuySellY, GetColor(255, 255, 255), mojibuf); // ������`�悷��


}

// int offsetYtemp1 = 100;

void shopKoumoku() {


	//BrushPink_set(hdc);
	//tenmetu(280, 200 + 60 + 30 * (whomTargetID1),		320 + 40, offsetYtemp1 + 60 + 60 + 30 * (whomTargetID1));

	//SetBkColor(hdc, RGB(0xFF, 0xFF, 0xFF));
	//SetBkMode(hdc, OPAQUE);

	// ���o��
	if (1) {
		lstrcpy(mojibuf, TEXT("���i��"));
		//TextOut(hdc, 280, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280, 200, GetColor(255, 255, 255), mojibuf); // ������`�悷��



		lstrcpy(mojibuf, TEXT("���i"));
		//TextOut(hdc, 280 + 120, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280 + 120, 200, GetColor(255, 255, 255), mojibuf); // ������`�悷��



		lstrcpy(mojibuf, TEXT("�݌�"));
		//TextOut(hdc, 280 + 170, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280 + 170, 200, GetColor(255, 255, 255), mojibuf); // ������`�悷��



		lstrcpy(mojibuf, TEXT("������"));
		//TextOut(hdc, 280 + 170 + 50, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280 + 170 + 50, 200, GetColor(255, 255, 255), mojibuf); // ������`�悷��

	}

}




void shopGoldRan() {


	//BrushBlue_set(hdc);
	int GoldRanX = 490; int GoldRanY = 50;

	window1Draw(GoldRanX, GoldRanY,
		GoldRanX + 120, 110);


	lstrcpy(mojibuf, TEXT("������"));


	DrawFormatString(GoldRanX, GoldRanY + 10, GetColor(255, 255, 255), mojibuf); // ������`�悷��



	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d G"), your_money);

	DrawFormatString(GoldRanX, GoldRanY + 10 + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��




}



void shopHinBack() {


	//SelectObject(hdc, blue_thin_1);
	window1Draw(250, 170, 560, 400);

	lstrcpy(mojibuf, TEXT("�����ɏ��i�⏊���i���\������܂�"));
	// TextOut(hdc, 280, 170, mojibuf, lstrlen(mojibuf));

	DrawFormatString(280, 170, GetColor(255, 255, 255), mojibuf); // ������`�悷��


}


void shopData() {

	if (shopMijissou == 1) {
		// ���蕨�̒�`
		// 1�i��
		// ��\��
		hinmoku[0].Grouptype = -99;
		hinmoku[0].subID = -99;

	}


	if (whomTargetID1 == 0) {
		// ���蕨�̒�`
		// 1�i��
		// strcpy_s(  hinmoku[0].ItemName, 10 ,"�ŏ���"); 
		hinmoku[0].Grouptype = wepoType;
		hinmoku[0].subID = 1;

		itemHairetu[0] = hinmoku[0].subID;
		itemTypeHairetu[0] = hinmoku[0].Grouptype;

		// 2�i��   
		hinmoku[1].Grouptype = wepoType;
		hinmoku[1].subID = 2;
		//strcpy_s( ItemYouso[1][1].ItemName, 10 ,"�S�̌�"); 


		// 3�i��   
		hinmoku[2].Grouptype = -99;
		hinmoku[2].subID = -99;
	}

	if (whomTargetID1 == 1) {
		// ���蕨�̒�`
		// 1�i��
	// strcpy_s(  hinmoku[0].ItemName, 10 ,"�ŏ���"); 
		hinmoku[0].Grouptype = tateType;
		hinmoku[0].subID = 1;


		// 2�i��   
		hinmoku[1].Grouptype = tateType;
		hinmoku[1].subID = 2;
		//strcpy_s( ItemYouso[1][1].ItemName, 10 ,"�S�̌�"); 


		// 3�i��   
		hinmoku[2].Grouptype = kabutoType;
		hinmoku[2].subID = 1;


		// 4�i��   
		hinmoku[3].Grouptype = kabutoType;
		hinmoku[3].subID = 2;


		// 5�i��   
		hinmoku[4].Grouptype = -99;
		hinmoku[4].subID = -99;
	}


	goukeiItem = 0;


	for (int aaa = 0; aaa <= 8; aaa = aaa + 1) {
		if (hinmoku[aaa].Grouptype == -99) {
			//range = aaa;
			break;
		}

		itemHairetu[aaa] = hinmoku[aaa].subID;
		itemTypeHairetu[aaa] = hinmoku[aaa].Grouptype;

		goukeiItem = goukeiItem + 1;
	}


}






// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�

	// SetUseSoftwareRenderModeFlag(TRUE); // �\�t�g�E�F�A�����_�����O�̃e�X�g

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);


	int mapchip1Handle = LoadGraph("GameData\\mapchip\\mapchip_grass.bmp");
	int mapchip2Handle = LoadGraph("GameData\\mapchip\\mapchip_wall.bmp");



	int treechip1Handle = LoadGraph("GameData\\mapchip\\tree.png");






	int monsHandle[10];
	int slimeHandle = LoadGraph("GameData\\monster_graphic\\slime.png");
	int koboHandle = LoadGraph("GameData\\monster_graphic\\kobo.png");


	monsHandle[0] = LoadGraph("GameData\\monster_graphic\\slime.png");
	monsHandle[1] = LoadGraph("GameData\\monster_graphic\\kobo.png");



	int monchipDownHandle = LoadGraph("GameData\\charachip\\enemy_dot.png");
	int blackchipHandle = LoadGraph("GameData\\charachip\\blackchip.bmp");


	//int blackbackHandle = LoadGraph("GameData\\picture\\blackBigBack.bmp");

	int townchipDownHandle = LoadGraph("GameData\\charachip\\town_dot.png");


	//int charachipUpHandle = LoadGraph("GameData\\charachip\\hero_dot_up.bmp");
	//int charachipDownHandle = LoadGraph("GameData\\charachip\\hero_dot_down.bmp");
	//int charachipLeftHandle = LoadGraph("GameData\\charachip\\hero_dot_left.bmp");
	//int charachipRightHandle = LoadGraph("GameData\\charachip\\hero_dot_right.bmp");







	int hitoHandle = LoadGraph("GameData\\charachip\\chara.png");
	int hitoM1Handle = LoadGraph("GameData\\charachip\\chara.png");
	int hitoM2Handle = LoadGraph("GameData\\charachip\\chara.png");



	int hitoSitaHandle = LoadGraph("GameData\\charachip\\chara_down.png");
	int hitoSitaM1Handle = LoadGraph("GameData\\charachip\\chara_down_m1.png");
	int hitoSitaM2Handle = LoadGraph("GameData\\charachip\\chara_down_m2.png");


	int hitoMigiHandle = LoadGraph("GameData\\charachip\\chara_right.png");
	int hitoMigiM1Handle = LoadGraph("GameData\\charachip\\chara_right_m1.png");
	int hitoMigiM2Handle = LoadGraph("GameData\\charachip\\chara_right_m2.png");


	int hitoHidariHandle = LoadGraph("GameData\\charachip\\chara_left.png");
	int hitoHidariM1Handle = LoadGraph("GameData\\charachip\\chara_left_m1.png");
	int hitoHidariM2Handle = LoadGraph("GameData\\charachip\\chara_left_m2.png");



	int hitoUpHandle = LoadGraph("GameData\\charachip\\chara_up.png");
	int hitoUpM1Handle = LoadGraph("GameData\\charachip\\chara_up_m1.png");
	int hitoUpM2Handle = LoadGraph("GameData\\charachip\\chara_up_m2.png");











	// �A�C�e���̏��
	int tourokuItem = 3;
	for (int temp = 0; temp <= tourokuItem; temp++) {

		item_def_list[temp].def_id = temp;
		item_def_list[temp].item_type = siyouType;

		if (temp == 0) {
			// �󔒂̒�`
			lstrcpy(item_def_list[temp].def_name, TEXT("--------"));
			item_def_list[temp].healti = 0;
		}

		if (temp == 1) {
			//�򑐂̒�`
			lstrcpy(item_def_list[temp].def_name, TEXT("��"));
			item_def_list[temp].healti = 5;
		}

		if (temp == 2) {
			lstrcpy(item_def_list[temp].def_name, TEXT("�ŏ�����"));
			item_def_list[temp].healti = 1;
		}

		if (temp == 3) {
			lstrcpy(item_def_list[temp].def_name, TEXT("�s�����̔�")); // �����̗��R�͎����̐ߖ�
			item_def_list[temp].healti = 2;
		}
	}



	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			(soubihin[temp].Stype[wepoType]).def_id = 0;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[wepoType]).material = mateNothing;
			(soubihin[temp].Stype[wepoType]).equip_type = typeNothing;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 0; // �U����
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			(soubihin[temp].Stype[wepoType]).def_id = 1;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("�S�̑�"));
			(soubihin[temp].Stype[wepoType]).material = mateIron;
			(soubihin[temp].Stype[wepoType]).equip_type = spear;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 107; // �U����	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[wepoType]).def_id = 2;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("�S�̃��C�X"));
			(soubihin[temp].Stype[wepoType]).material = mateIron;
			// weapon_def_list[temp].equip_type = spear;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 44; // �U����
			continue;
		}
	}


	//�h��̒�` �^�e
// �v�Z�ʂ�2�掞�Ԃ̃A���S���Y�������ǁA�Ƃ肠�����ҏW����o�O�ϐ���D�悵�A�v�Z���Ԃ͍l�����Ȃ��B
// �ǂ����Ă��v�Z���Ԃ�Z�k�������Ȃ�Aif��switch-break�ɒu��������΁A�ǂݍ��ݎ��Ԃ��኱�A���点�邩�B
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 0; // �U����
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("�؂̏�"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 5; // �U����	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("�S�̏�"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 30; // �U����
			continue;
		}
	}


	//�h��̒�` �J�u�g	
	// �v�Z�ʂ�2�掞�Ԃ̃A���S���Y�������ǁA�Ƃ肠�����ҏW����o�O�ϐ���D�悵�A�v�Z���Ԃ͍l�����Ȃ��B	
	// �ǂ����Ă��v�Z���Ԃ�Z�k�������Ȃ�Aif��switch-break�ɒu��������΁A�ǂݍ��ݎ��Ԃ��኱�A���点�邩�B
	for (int temp = 0; temp <= 10; temp = temp + 1) {
		int locType = kabutoType;
		if (temp == 0) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 0; // �U����
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("�؂̖X�q"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 50; // �U����	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("�S�̃J�u�g"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 20; // �U����
			continue;
		}
	}


	//�h��̒�` �����C
	// �v�Z�ʂ�2�掞�Ԃ̃A���S���Y�������ǁA�Ƃ肠�����ҏW����o�O�ϐ���D�悵�A�v�Z���Ԃ͍l�����Ȃ��B
	// �ǂ����Ă��v�Z���Ԃ�Z�k�������Ȃ�Aif��switch-break�ɒu��������΁A�ǂݍ��ݎ��Ԃ��኱�A���点�邩�B
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("--------"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 0; // �U����
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("��̕�"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 2; // �U����
			continue;
		}

		if (temp == 2) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("�؂̃����C"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 5; // �U����
			continue;
		}


		if (temp == 3) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("�������т�"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 10; // �U����
			continue;
		}
	}



	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			magic_def_list[temp].def_id = temp;
			lstrcpy(magic_def_list[temp].def_name, TEXT("�t�@�C�A"));
			magic_def_list[temp].power = 1000;
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			magic_def_list[temp].def_id = temp;
			lstrcpy(magic_def_list[temp].def_name, TEXT("�A�C�X"));
			magic_def_list[temp].power = 100;
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

	}




	//�����A�C�e���̌��Ȃǂ̏����l
	for (int temp = 0; temp <= tourokuItem; temp++) {

		item_have_list[temp].have_def_id = temp + 1;

		if (temp == 0) {
			item_have_list[temp].have_kosuu = 0;
		}
		if (temp == 1) {
			item_have_list[temp].have_kosuu = 5;
		}

		if (temp == 2) {
			item_have_list[temp].have_kosuu = 4;
		}

		if (temp == 3) {
			item_have_list[temp].have_kosuu = 2;
		}
	}


	//�����̑����i�̌��Ȃǂ̏����l
	for (int temp = 0; temp <= 15 - 1; temp++) {

		int locType = wepoType;
		soubiSyoji[temp].Stype[locType].have_def_id = temp + 1;

		if (temp == 0) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0; // --------
		}

		if (temp == 1) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0;
		}

		if (temp == 2) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 3;
		}
	}



	for (int temp = 0; temp <= 15 - 1; temp++) {

		//
		int locType = tateType;
		soubiSyoji[temp].Stype[locType].have_def_id = temp + 1;

		if (temp == 0) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0; // --------
		}

		if (temp == 1) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 1;
		}

		if (temp == 2) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0;
		}
	}


	for (int temp = 0; temp <= 15 - 1; temp++) {

		//
		int locType = kabutoType;
		soubiSyoji[temp].Stype[kabutoType].have_def_id = temp + 1;

		if (temp == 0) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0; // --------
		}

		if (temp == 1) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 5;
		}

		if (temp == 2) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0;
		}
	}



	//���������̕���

	int equipInitialWeaponId = 1;
	equipWeaponPower = weapon_def_list[equipInitialWeaponId].equipPower;


	// map�̏��
	for (int temp = 0; temp <= 1; temp++) {

		if (temp == 0) {
			// map1 �ɂ���}�b�v�J�ڂ̏��
			MapTrans_def_list[temp].MapTrans_id = 1; // ���̃}�b�v���ŉ��Ԗڂ��H
			MapTrans_def_list[temp].in_Where_Map = 1; // map ����?
			MapTrans_def_list[temp].to_Where_Map = 2;
			MapTrans_def_list[temp].positionX = 7;
			MapTrans_def_list[temp].positionY = 6;

			MapTrans_def_list[temp].chara_positionX = 2;
			MapTrans_def_list[temp].chara_positionY = 1;
		}

		if (temp == 1) {
			// map2 �ɂ���}�b�v�J�ڂ̏��
			MapTrans_def_list[temp].MapTrans_id = 1;
			MapTrans_def_list[temp].in_Where_Map = 2; // map ����?
			MapTrans_def_list[temp].to_Where_Map = 1;
			MapTrans_def_list[temp].positionX = 2;
			MapTrans_def_list[temp].positionY = 0;

			MapTrans_def_list[temp].chara_positionX = 7;
			MapTrans_def_list[temp].chara_positionY = 4;
		}
	}


	// [30]�͕������ł��邱�Ƃɒ���
	TCHAR TekiList[5][5][30] = {
		{TEXT("1"),TEXT("�X���C��"), },
		{TEXT("2"),TEXT("�R�{���g"),}
	};

	int TekiParam1[8][10] = {

		//= {id, LV, HPM, };
			{ 1, 1, 13  , },
			{ 2, 1, 400,}

	};


	int TekiParam2[8][10] = {

		//   id ,atk,agi,  
			{ 1, 0, 13  },
			{ 2, 1, 76}

	};


	int TekiParam3[8][10] = {

		//   id ,exp,gold,  
			{ 1, 2, 1  },
			{ 2, 5, 10}

	};




	// �����X�^�[�̒�`	
	for (int temp = 0; temp <= 1; temp++) {


		lstrcpy(monster_def_list[temp].monster_name, TekiList[temp][1]);

		monster_def_list[temp].monster_id = TekiParam1[temp][0];
		monster_def_list[temp].mon_hp_max = TekiParam1[temp][2];

		monster_def_list[temp].mon_attackPower = TekiParam2[temp][1];
		monster_def_list[temp].mon_agility = TekiParam2[temp][2];

		monster_def_list[temp].mon_exp = TekiParam3[temp][1];
		monster_def_list[temp].mon_gold = TekiParam3[temp][2];

	}

	// �����I�Ƀf�[�^�x�[�X�̏��������Ɍ����Ĕz��e�X�g
	// const�����Ȃ��B����ł͒萔�����A�����̃f�[�^�x�[�X�ǂݍ��ݎ��ɉςƂ��Ďg���̂�
	//                 =  {id, LV,HP,HPM, agi};
	int NakamaParam1[8][10] = { { 0,1,132,140,56, },
							{ 1,1,108,150,100,}

	};

	// �o���l�Ƃ�
	//                       id,exp
	int NakamaParam2[8][10] = { { 0,0,0,0, },
							{ 1,0,0,0,}

	};

	// ��ԃX�e�[�^�X�̃t���O
	//                       id,death,
	int NakamaJotai[8][10] = { { 0,0,0,0, },
							{ 1,0,0,0,}

	};



	// �z��ł́A�{�Ԃł�CSV�t�@�C����g�ݍ���ŁA�����ǂݍ���Ŕz��ɑ������X�^�C����z��B
	// �����_�ł͊J���i�K�Ȃ̂ŁACSV�͖��쐬�B�G�N�Z���g���̖ʓ|�����B

	// TCHAR tesqqq[30] = TEXT("aaaa"); // �׋��p // TCHAR�̍Ō��[ ]�͕��������ƖY���ȁB

	// [30]�͕������ł��邱�Ƃɒ���
	TCHAR NakamaList[5][5][30] = {
		{TEXT("0"),TEXT("�G���X"), },
		{TEXT("1"),TEXT("�s�G�[��"),}
	};



	// �����̃t���O
	//                       id,wep,tate,kabu,
	int NakamaEquipList[8][10] = { { 0, 1,   1,  0, },
							{ 1, 2,   0,  0,}

	};


	// �����J�[�\���̈ʒu�B���̃Q�[���ɂ́A���ꂪ����񂾂���
	//                       id,wep,tate,kabu,
	int NakamaKasolEquip[8][10] = { { 0, 0,   0,  0, },
							{ 1, 0,   0,  0,}

	};



	// �p�[�e�B�����t���O
	// ���}���u
	int PartyInFlag[8][10] = { { 0, 1,   0,  0, },
							{ 1, 1,   0,  0,}

	};


	// �L�����N�^�[�̒�`
	for (int temp = 0; temp <= makeNakamaNinzu + 1; temp++) {

		// �L����0�ƃL����1�̏����l������W���[���̌����e�X�g
		for (int temp = 0; temp <= 1; temp++) {


			lstrcpy(heros_def_list[temp].heros_name, NakamaList[temp][1]);

			heros_def_list[temp].heros_hp = NakamaParam1[temp][2]; // 132; // 132   20;
			heros_def_list[temp].heros_hp_max = NakamaParam1[temp][3]; // 140;
			heros_def_list[temp].heros_agility = NakamaParam1[temp][4]; // 56;

			heros_def_list[temp].heros_exp = NakamaParam2[temp][1];

			heros_def_list[temp].heros_HP0_flag = NakamaJotai[temp][1];
			heros_def_list[temp].PartyIn = PartyInFlag[temp][1];


			heros_def_list[temp].heroSoubi[wepoType] = NakamaEquipList[temp][1];
			heros_def_list[temp].heroSoubiKasol[wepoType] = NakamaKasolEquip[temp][1];

			heros_def_list[temp].heroSoubi[tateType] = NakamaEquipList[temp][2];

			heros_def_list[temp].heros_para[kougekiPara] = (soubihin[heros_def_list[temp].heroSoubi[wepoType]].Stype[wepoType]).equipPower[kougekiPara];

			heros_def_list[temp].heros_para[syubiPara] = (soubihin[heros_def_list[temp].heroSoubi[tateType]].Stype[tateType]).equipPower[syubiPara]
				+ (soubihin[heros_def_list[temp].heroSoubi[kabutoType]].Stype[kabutoType]).equipPower[syubiPara]
				;

		}


		if (temp == 2) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("�S���U���X"));
			heros_def_list[temp].heros_hp = 5; // 55;
			heros_def_list[temp].heros_hp_max = 55;
			heros_def_list[temp].heros_agility = 55;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;

			heros_def_list[temp].heros_shield = 1;
		}

		if (temp == 3) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("�y�h��"));
			heros_def_list[temp].heros_hp = 10;// 12;
			heros_def_list[temp].heros_hp_max = 34;
			heros_def_list[temp].heros_agility = 23;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;

			heros_def_list[temp].heros_shield = 0;
		}


		if (temp == 4) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("�e�X�g�p�L����"));
			heros_def_list[temp].heros_hp = 10;// 12;
			heros_def_list[temp].heros_hp_max = 34;
			heros_def_list[temp].heros_agility = 23;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;
		}

	}

	akikosuu = partymax - partyNinzuDone;

	partyNarabijyun[0] = 0; // 
	partyNarabijyun[1] = 1;
	partyNarabijyun[2] = -1; // �}�C�i�X�ԂȂ�A�����ŏI��

	// �j���[�Q�[���̎��_�ŁA�퓬�s�\�t���O���X�V
	for (int temp = 0; temp < tourokuNakama; ++temp) {

		if (heros_def_list[temp].heros_hp < 1) {
			heros_def_list[temp].heros_hp = 0;

			// �퓬�s�\�t���O���I��
			heros_def_list[temp].heros_HP0_flag = 1;
		}

		if (heros_def_list[temp].heros_hp >= 1) {
			// �퓬�s�\�t���O��OFF
			heros_def_list[temp].heros_HP0_flag = 0;
		}
	}


	int tempHairetu[BATTLE_Agility_proc + 1]; // �g��Ȃ�����?

	tempHairetu[0] = 0;
	tempHairetu[1] = -99;
	memcpy(monsterTairetu_def_list[0].monsterTairetu, tempHairetu, sizeof(tempHairetu));

	tempHairetu[0] = 1;
	tempHairetu[1] = -99;
	memcpy(monsterTairetu_def_list[1].monsterTairetu, tempHairetu, sizeof(tempHairetu));




	struct treetype {
		int posiX;
		int posiY;
	};

	static struct treetype treehen[20]; // �\���̔z��̐錾

	treehen[0] = { 5,4 };

	int treex = 5; int treey = 4;

	for (int temp = 0; temp <= 0; temp = temp + 1) {
		//DrawGraph(mapChipWidthX * treehen[temp].posiX, mapChipWidthY * (treehen[temp].posiY - 1) - 5, treechip1Handle, true);

		maptreetable[treehen[temp].posiY][treehen[temp].posiX] = 1;
	}



	for (int y = 0; y <= 7; y = y + 1) {
		for (int x = 0; x <= 10; x = x + 1) {

			if (y == treehen[0].posiY && x == treehen[0].posiX) {
				maptreelayer[y][x] = 2;
			}

			//if (y == treehen[0].posiY && x == treehen[0].posiX) {
			//	maptreelayer[y][x] = 1; // �ʍs���s�\
			//}
		}
	}



	for (int y = 0; y <= 7; y = y + 1) {
		for (int x = 0; x <= 10; x = x + 1) {

			if (maptreelayer[y][x] == 0) {
				maptukotable[y][x] = 0;
			}

			if (maptreetable[y][x] == 1 || map1table[y][x]) {
				maptukotable[y][x] = 1; // �ʍs���s�\
			}
		}
	}






	while (1) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}

		ClearDrawScreen();

		if (keyEnableZ == 0 && nyuuryokuMatiZ > 0) {
			nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

		}
		if (nyuuryokuMatiZ <= 0) {
			nyuuryokuMatiZ = 0;
			keyEnableZ = 1;
		}

		if (nyuuryokuMatiX > 0) {
			nyuuryokuMatiX = nyuuryokuMatiX - 1;

		}

		if (nyuuryokuMatiX <= 0) {
			nyuuryokuMatiX = 0;
			keyEnableX = 1;

		}

		// �o�O�h�~ �L�[���͉\�Ȃ�ҋ@�̕K�v�Ȃ��̂�
		if (keyEnableUp == 1) {
			nyuuryokuMatiUp = 0;

		}
		if (keyEnableDown == 1) {
			nyuuryokuMatiDown = 0;

		}


		if (keyEnableUp == 0 ) {
			nyuuryokuMatiUp = nyuuryokuMatiUp - 1;

		}

		if (nyuuryokuMatiUp <= 0) {
			nyuuryokuMatiUp = 0;
			keyEnableUp = 1;
		}

		if (nyuuryokuMatiDown > 0) {
			nyuuryokuMatiDown = nyuuryokuMatiDown - 1;
		}

		if (nyuuryokuMatiDown <= 0) {
			nyuuryokuMatiDown = 0;
			keyEnableDown = 1;
		}


		if (keyEnableLeft == 0 && nyuuryokuMatiLeft > 0) {
			nyuuryokuMatiLeft = nyuuryokuMatiLeft - 1;

		}
		if (nyuuryokuMatiLeft <= 0) {
			nyuuryokuMatiLeft = 0;
			keyEnableLeft = 1;


		}

		if (nyuuryokuMatiRight > 0) {
			nyuuryokuMatiRight = nyuuryokuMatiRight - 1;

		}

		if (nyuuryokuMatiRight <= 0) {
			nyuuryokuMatiRight = 0;
			keyEnableRight = 1;

		}



		// �}�b�v�`��

		static int mapChipWidthX = 32;
		static int mapChipWidthY = 32;


		static int charaChipWidthX = 32; // ����if�̊O�ł��g���̂Ńu���b�N�O�Œ�`�B
		static int charaChipWidthY = 32;

		static double baiX = waitTime1 / charaChipWidthX; static double baiY = waitTime1 / charaChipWidthY;

		static int tempK = 1;






		// �}�b�v���ɂ��郂���X�^�[�V���{����璬���̃}�X�ʒu������킷�\����
		// �}�b�v�C�x���g�p�Ɏg������
		struct Posi_def
		{
			int PosiX;
			int PosiY;

			// int tempHandle; // ���łɃO���[�o���ϐ��œ��l�̐����`����
		};

		static struct Posi_def* tempEvAdr;


		// ���͔w�i�ɏ�����̂ŁA�����X�^�[����ɕ`��B�������}�b�v�C�x���g�ł���̂ŁA�w�i�Ƃ͋�ʂ̕K�v����B
		// �}�b�v�C�x���g�̃^�E���p

		static struct Posi_def town[15];

		tempHandle = townchipDownHandle;


		for (int temp = 0; temp <= 0; temp = temp + 1) {

			// �����W
			// 2,5

			town[temp].PosiX = town_X;
			town[temp].PosiY = town_Y;

		}

		int tempTourokusuu1;

		tempTourokusuu1 = 1;

		tempEvAdr = town;

		struct localFuncStruct
		{
			void localDraw(int temp) {
				 DrawGraph(mapChipWidthX * (*(tempEvAdr + temp)).PosiX, mapChipWidthY * (*(tempEvAdr + temp)).PosiY, tempHandle, true);
				
				// DrawGraph(mapChipWidthX * town[temp].PosiX, mapChipWidthY * town[temp].PosiY, tempHandle, true);

			}


		} localFunc;

		// �}�b�v���̒��̃h�b�g
		for (int temp = 0; temp <= tempTourokusuu1 - 1; temp = temp + 1) {

			// ���摜
			localFunc.localDraw(temp);
			//DrawGraph(mapChipWidthX * (*(tempEvAdr+temp)).PosiX, mapChipWidthY * (*(tempEvAdr+temp)).PosiY, tempHandle, false);

		}



		// �����X�^�[�̈ʒu���
		static struct Posi_def monEv[15];


		tempHandle = monchipDownHandle;

		for (int temp = 1; temp <= 2; temp = temp + 1) {
			//if (enemy_alive[mapEneNum] == 1) {

			monEv[temp - 1].PosiX = monPosiX[temp - 1];
			monEv[temp - 1].PosiY = monPosiY[temp - 1];

		}


		tempEvAdr = monEv;

		// �}�b�v���̃����X�^�[�̃h�b�g
		// tempTouroku �̓����X�^�[�o�^��
		tempTourokusuu1 = 2;

		for (int temp = 0; temp <= tempTourokusuu1 - 1; temp = temp + 1) {
			//if (enemy_alive[mapEneNum] == 1) {

				// ���S�p�̕��� �P�\�J�E���^�[�������X�^�[�����t���O�Ƃ��ė��p���Ă�̂ŁA���L�ɂȂ�
			if (toubouTyokugo[temp] == 0) {
				// �����X�^�[�摜
				localFunc.localDraw(temp);

			}

			if (toubouTyokugo[temp] > 0 && enemy_alive[temp] == 1) {
				// �����X�^�[�摜

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				localFunc.localDraw(temp);

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}

			//}
		}







		for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw)
		{
			for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)
			{
				if (map1table[y_mapDraw][x_mapDraw] == 0) {
					DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * y_mapDraw, mapchip1Handle, false);
				}
				if (map1table[y_mapDraw][x_mapDraw] == 1) {
					DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * y_mapDraw, mapchip2Handle, false);
				}
			}


			for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)
			{
				if (maptreelayer[y_mapDraw][x_mapDraw] == 0) {
					//DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * y_mapDraw, mapchip1Handle, false);
				}
				if (maptreelayer[y_mapDraw][x_mapDraw] == 2) {
					DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * (y_mapDraw - 1), treechip1Handle, true);
				}



				for (int temp = 0; temp <= 0; temp = temp + 1) {
					if (y_mapDraw == town[temp].PosiY  && x_mapDraw == town[temp].PosiX) {

						tempHandle = townchipDownHandle;

						DrawGraph(mapChipWidthX * town[temp].PosiX, mapChipWidthY * town[temp].PosiY, tempHandle, false);
					}
				}



				for (int temp = 0; temp <= 1; temp = temp + 1) {
					if (y_mapDraw == monEv[temp].PosiY && x_mapDraw == monEv[temp].PosiX) {
						
						tempHandle = monchipDownHandle;

						if (toubouTyokugo[temp] == 0) {
							// �����X�^�[�摜
							localFunc.localDraw(temp);

						}

						if (toubouTyokugo[temp] > 0 && enemy_alive[temp] == 1) {
							// �����X�^�[�摜

							//tempHandle = monchipDownHandle;
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
							localFunc.localDraw(temp);

							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
					}
				}






				if (y_mapDraw == yPosi && x_mapDraw == xPosi) {


					//

#define macroDraw1()  DrawGraph(charaChipWidthX* xPosi + 0 + K * (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY* yPosi, tempHandle, false)

		//	__inline void inDraw() { // �G���[
		//		DrawGraph(charaChipWidthX * xPosi + 0 + K * (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY * yPosi, tempHandle, false);
		//	}

					if (hero1_direction == rightward && moving == 1) {
						tempK = 1;


						//tempHandle = charachipRightHandle;
						// localFunc.localDraw1();
#define K 1
						// DrawGraph(charaChipWidthX * xPosi + 0 + K * (waitTime1 - nyuuryokuMatiLR) / (baiX+1.5), charaChipWidthY * (yPosi - 1), hitoHandle, true);

						// static double ttttt = nyuuryokuMatiLR / waitTime1;
						
						if (nyuuryokuMatiLR > 40 - 14 * 1 ) {
							DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoMigiM1Handle, true);
						}

						if (nyuuryokuMatiLR >= 40 - 14 * 2 && nyuuryokuMatiLR <= 40 - 14 * 1 ) {
							DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoMigiM2Handle, true);
						}

						if (nyuuryokuMatiLR < 40 - 14 * 2 ) {
							DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoMigiHandle, true);
						}

						//macroDraw1();
						//DrawGraph(charaChipWidthX* xPosi + 0 + K * (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY* yPosi, tempHandle, false);
#undef K
					}





					else if (hero1_direction == rightward && moving != 1) {
						tempK = 1;
						//tempHandle = charachipRightHandle;
						// localFunc.localDraw1();
#define K 0
						DrawGraph(charaChipWidthX* xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY* (yPosi - 1), hitoMigiHandle, true);



						//macroDraw1();
						//DrawGraph(charaChipWidthX* xPosi + 0 + K * (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY* yPosi, tempHandle, false);
#undef K
					}







					if (hero1_direction == leftward && moving == 1) {
						tempK = -1;

						//tempHandle = charachipLeftHandle;
						// localFunc.localDraw1();

#define K -1 
						//DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoHidariHandle, true);


						if (nyuuryokuMatiLR > 40 - 14 * 1) {
							DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoHidariM1Handle, true);
						}

						if (nyuuryokuMatiLR >= 40 - 14 * 2 && nyuuryokuMatiLR <= 40 - 14 * 1) {
							DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoHidariM2Handle, true);
						}

						if (nyuuryokuMatiLR < 40 - 14 * 2) {
							DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoHidariHandle, true);
						}


						//macroDraw1();
						//DrawGraph(charaChipWidthX* xPosi + 0 + K * (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY* yPosi, tempHandle, false);
#undef K
					}

					else if (hero1_direction == leftward && moving != 1) {
						tempK = -1;

						//tempHandle = charachipLeftHandle;
						// localFunc.localDraw1();

#define K 0 
						DrawGraph(charaChipWidthX* xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY* (yPosi - 1), hitoHidariHandle, true);


	

						//macroDraw1();
						//DrawGraph(charaChipWidthX* xPosi + 0 + K * (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY* yPosi, tempHandle, false);
#undef K
					}






#undef macroDraw1() 


#define macroDraw2() DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* yPosi + K * (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);


					// �ړ����ĂȂ��������͎c���Ȃ��ƕ\����������
					if (hero1_direction == downward && moving != 1) {
						tempK = -1;



						//tempHandle = charachipDownHandle;
						//localFunc.localDraw2();
#define K 0
						DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoSitaHandle, true);

						//macroDraw2();
						//DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* yPosi + K * (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);
#undef K
					}






					if (hero1_direction == upward && moving == 1) {
						tempK = -1;



						//tempHandle = charachipUpHandle;
						//localFunc.localDraw2();
#define K -1
						//DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoUpHandle, true);


						if (nyuuryokuMatiUD > 40 - 14 * 1) {
							DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoUpHandle, true);

							
							//DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoSitaHandle, true);
							//DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoHidariM1Handle, true);
						}

						if (nyuuryokuMatiUD >= 40 - 14 * 2 && nyuuryokuMatiUD <= 40 - 14 * 1) {
							DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoUpM1Handle, true);

							//DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoSitaM1Handle, true);
						}

						if (nyuuryokuMatiUD < 40 - 14 * 2) {
							DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoUpM2Handle, true);

							//DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoSitaM2Handle, true);
						}



						//macroDraw2();
						//DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* yPosi + K * (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);
#undef K
					}

					else if (hero1_direction == upward && moving != 1) {
						tempK = -1;



						//tempHandle = charachipUpHandle;
						//localFunc.localDraw2();
#define K 0
						DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoUpHandle, true);

						//macroDraw2();
						//DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* yPosi + K * (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);
#undef K
					}



#undef macroDraw2() 


				} // if (y_mapDraw == yPosi && x_mapDraw == xPosi) {




				// ���Ɉړ����̂Ƃ��A����Ȃ��Ɖ����g��������

				if (y_mapDraw == yPosi + 1 && x_mapDraw == xPosi && hero1_direction == downward && moving == 1) {


#define macroDraw2() DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* yPosi + K * (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);

					if (hero1_direction == downward && moving == 1) {
						tempK = 1;





						// tempHandle = charachipDownHandle;
#define K 1



						if (nyuuryokuMatiUD > 40 - 14 * 1) {
							DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoSitaHandle, true);
							//DrawGraph(charaChipWidthX * xPosi + 0 + K * charaChipWidthX * (waitTime1 - nyuuryokuMatiLR) / waitTime1, charaChipWidthY * (yPosi - 1), hitoHidariM1Handle, true);
						}

						if (nyuuryokuMatiUD >= 40 - 14 * 2 && nyuuryokuMatiUD <= 40 - 14 * 1) {
							DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoSitaM1Handle, true);
						}

						if (nyuuryokuMatiUD < 40 - 14 * 2) {
							DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoSitaM2Handle, true);
						}




						//DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* (yPosi - 1) + K * charaChipWidthY * (waitTime1 - nyuuryokuMatiUD) / waitTime1, hitoHandle, true);

						//macroDraw2();
						//DrawGraph(charaChipWidthX* xPosi + 0, charaChipWidthY* yPosi + K * (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);
#undef K

				//localFunc.localDraw2();
					}

#undef macroDraw2() 


				} // if (y_mapDraw == yPosi && x_mapDraw == xPosi) {




			} // for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)



		} // for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw) // y�̂ق�













		// �L�����`�b�v�`��
		{

			if (toubouTyokugo[(encount_monsters_id)-1] > 0 && enemy_alive[(encount_monsters_id)-1] == 1 && xPosi == monPosiX[1 - 1] && yPosi == monPosiY[1 - 1]) {

				// ���S���ɏd�Ȃ��Ă������X�^�[�\�����Ȃ��悤�ɂ��鏈��
				// DrawGraph(charaChipWidthX * monPosiX[(encount_monsters_id)-1], charaChipWidthY * monPosiY[(encount_monsters_id)-1], blackchipHandle, false);

			}



			// �ʂ̌����̉摜�ŏ㏑��



			struct localFuncStruct
			{
				void localDraw1() {
					DrawGraph(charaChipWidthX * xPosi + 0 + tempK * (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY * yPosi, tempHandle, false);
				}

				void localDraw2() {
					DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * yPosi + tempK * (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);

				}
			} localFunc;







			for (int temp = 0; temp <= 0; temp = temp + 1) {
				// DrawGraph(mapChipWidthX * treehen[temp].posiX, mapChipWidthY * (treehen[temp].posiY - 1) - 5, treechip1Handle, true);

				//maptreetable[treehen[temp].posiY][treehen[temp].posiX] = 1;
			}



			//maptreetable[][]=1;


			if (mode_scene == MODE_MAP) {
				// �ړ��L�[�̃t���O����
				{
					int mapsizeX = 10; int mapsizeY = 7;





					{ // �ړ��̃��W���[��






						enum nextDirect { up, down, right, left, non };
						enum nextDirect nextDirect_var = non;
						int nextDirFlag = 0;

						if(CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1 && moving == 1 && nextDirFlag == 0 && nyuuryokuMatiLR <5) {
							nextDirect_var = right;
						
						}




						// �L�������E�Ɉړ�
						if (xPosi < mapsizeX && yPosi < mapsizeY + 1) { // y���� ��+1 ���Ă�̂̓f�o�b�O�p
							// �ړ���\��n�̓���ۂ̔���

							if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1 && moving == 0) {
								hero1_direction = rightward;

								if (maptukotable[yPosi][xPosi + 1] == 1) { destMovable = 0; }
								if (maptukotable[yPosi][xPosi + 1] == 0) { destMovable = 1; }

								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi == monPosiY[temp - 1] && xPosi + 1 == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive �ȂǂŎg��


										int taiou[10] = { 2,1,0,0,0,0 }; // �G���J�E���g0�Ԗڂ͓Gid2(�R�{���g)���o���A�̈Ӗ�

										encount_monsters_id = taiou[temp - 1]; // �u���b�N�ŗL�̗v�f
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}


								//if (yPosi == treehen[0].posiY && xPosi + 1 == treehen[0].posiX ) { destMovable = 0; }

								// ����\�Ȃ�t���O�ݒ�
								if (destMovable == 1) {
									moving = 1;

									keyEnableRight = 0;
									nyuuryokuMatiLR = waitTime1;
								}
							}
							// �J�E���g����
							if (moving == 1 && nyuuryokuMatiLR > 0) {
								nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
							}
							// �ړ��̏I������
							if (hero1_direction == rightward && moving == 1 && nyuuryokuMatiLR <= 0) {
								keyEnableRight = 1; // moving �񕜂܂łɎ��Ԃ��|����̂ŁA������1�ɁB

								nyuuryokuMatiLR = waitTime1  ;
								nyuuryokuMatiLeft = waitTime1  ;
								nyuuryokuMatiRight = waitTime1  ;


								xPosi++;     // �E��1�}�X�����ړ�
								moving = 0;

								townFlag = 0;
							}
						} // �E�ړ�

						// ���Ɉړ�
						if (xPosi < mapsizeX + 1 && yPosi < mapsizeY + 1) {      // y���� ��+1 ���Ă�̂̓f�o�b�O�p
							// �ړ���\��n�̓���ۂ̔���
							if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1 && moving == 0) {
								hero1_direction = leftward;

								if (maptukotable[yPosi][xPosi - 1] == 1) { destMovable = 0; }
								if (maptukotable[yPosi][xPosi - 1] == 0) { destMovable = 1; }

								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi == monPosiY[temp - 1] && xPosi - 1 == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive �ȂǂŎg��


										int taiou[10] = { 2,1,0,0,0,0 }; // �G���J�E���g0�Ԗڂ͓Gid2(�R�{���g)���o���A�̈Ӗ�

										encount_monsters_id = taiou[temp - 1]; // �u���b�N�ŗL�̗v�f
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}


								//if (yPosi == treehen[0].posiY && xPosi - 1 == treehen[0].posiX) { destMovable = 0; }

								// ����\�Ȃ�t���O�ݒ�
								if (destMovable == 1) {
									moving = 1;

									keyEnableLeft = 0;
									nyuuryokuMatiLR = waitTime1;
								}
							}
							// �J�E���g����
							if (moving == 1 && nyuuryokuMatiLR > 0) {
								nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
							}
							// �ړ��̏I������
							if (hero1_direction == leftward && moving == 1 && nyuuryokuMatiLR <= 0) {
								keyEnableLeft = 1;

								nyuuryokuMatiLR = waitTime1;
								nyuuryokuMatiLeft = waitTime1;
								nyuuryokuMatiRight = waitTime1;

								xPosi--;    // ����1�}�X�����ړ�
								moving = 0;

								townFlag = 0;
							}
						}// ���Ɉړ�

						// ���Ɉړ�
						if (xPosi < mapsizeX && yPosi < mapsizeY) {
							// �ړ���\��n�̓���ۂ̔���
							if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1 && moving == 0) {
								hero1_direction = downward;

								if (maptukotable[yPosi + 1][xPosi] == 1) { destMovable = 0; }
								if (maptukotable[yPosi + 1][xPosi] == 0) { destMovable = 1; }

								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi + 1 == monPosiY[temp - 1] && xPosi == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive �ȂǂŎg��


										int taiou[10] = { 2,1,0,0,0,0 }; // �G���J�E���g0�Ԗڂ͓Gid2(�R�{���g)���o���A�̈Ӗ�

										encount_monsters_id = taiou[temp - 1]; // �u���b�N�ŗL�̗v�f
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}



								//if (yPosi +1 == treehen[0].posiY && xPosi == treehen[0].posiX) { destMovable = 0; }

								// ����\�Ȃ�t���O�ݒ�
								if (destMovable == 1) {
									moving = 1;

									keyEnableDown = 0;


									nyuuryokuMatiUD = waitTime1;
									nyuuryokuMatiUp = waitTime1;
									nyuuryokuMatiDown = waitTime1;

								}
							}

							// �J�E���g����
							// keyEnable�͕ʂ̃u���b�N�ŗ��p���Ă�̂ŁA�K�� moving ==1 ���K�v
							if (nyuuryokuMatiUD > 0 && moving == 1) {
								nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
							}
							// �ړ��̏I������
							if (hero1_direction == downward && nyuuryokuMatiUD <= 0 && moving == 1) {
								keyEnableDown = 1;

								nyuuryokuMatiUD = waitTime1;
								nyuuryokuMatiUp = waitTime1;
								nyuuryokuMatiDown = waitTime1;

								yPosi++;     // ����1�}�X�����ړ�
								moving = 0;

								townFlag = 0;
							}
						}// ���Ɉړ�


						// ��Ɉړ�
						if (xPosi < mapsizeX && yPosi < mapsizeY + 1) {
							// �ړ���\��n�̓���ۂ̔���
							if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && moving == 0) {
								hero1_direction = upward;

								if (maptukotable[yPosi - 1][xPosi] == 1) { destMovable = 0; }
								if (maptukotable[yPosi - 1][xPosi] == 0) { destMovable = 1; }

								//int temp = 1;
								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi - 1 == monPosiY[temp - 1] && xPosi == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive �ȂǂŎg��


										int taiou[10] = { 2,1,0,0,0,0 }; // �G���J�E���g0�Ԗڂ͓Gid2(�R�{���g)���o���A�̈Ӗ�

										encount_monsters_id = taiou[temp - 1]; // �u���b�N�ŗL�̗v�f
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}



								//if (yPosi - 1 == treehen[0].posiY && xPosi == treehen[0].posiX) { destMovable = 0; }


								// ����\�Ȃ�t���O�ݒ�
								if (destMovable == 1) {
									moving = 1;

									keyEnableUp = 0;

									nyuuryokuMatiUD = waitTime1;
									nyuuryokuMatiUp = waitTime1;
									nyuuryokuMatiDown = waitTime1;

								}
							}
							// �J�E���g����

							// keyEnable�͕ʂ̃u���b�N�ŗ��p���Ă�̂ŁA�K�� moving ==1 ���K�v
							if (nyuuryokuMatiUD > 0 && moving == 1) {
								nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
							}
							// �ړ��̏I������
							if (hero1_direction == upward && nyuuryokuMatiUD <= 0 && moving == 1) {
								keyEnableUp = 1;

								nyuuryokuMatiUD = waitTime1;
								nyuuryokuMatiUp = waitTime1;
								nyuuryokuMatiDown = waitTime1;

								yPosi--;     // ���1�}�X�����ړ�
								moving = 0;

								townFlag = 0;
							}
						}// ��Ɉړ�
					}// �ړ�

					// �G�����J�E���^�[
					// ���S�����̃t���O�ݒ���ۂ�
					// ���Ԃ�A�������тɓ��S��������p�̃J�E���^�[��+1����

					for (int temp = 1; temp <= 2; temp = temp + 1) {
						if (destMovable == 1 && moving == 1 && toubouTyokugo[temp - 1] > 0) {
							toubouTyokugo[temp - 1] = toubouTyokugo[temp - 1] - 1;
							destMovable = 0;

							// townFlag = 0; // ������o�����������łɁB // �������Ȃ�
						}
						if (toubouTyokugo[temp - 1] <= 0) {
							// toubouSeikou = 0; // ����Ȃ��ƍĐ펞�ɓ��S�������b�Z�[�W���o�Ă��܂� // ���ꂾ�ƃ}�b�v���Ɉ�C�ł��퓬�\�����X�^�[�������0�Z�b�g�ɂȂ�
							toubouTyokugo[temp - 1] = 0;

							enemy_alive[temp - 1] = 1; // �G���|����Ă��ꍇ�͕�������悤��
						}
					}

					// �����X�^�[�����̃G���J�E���g����
					{
						int monMesX = 400; int monMesY = 350; // ���b�Z�[�W���̕\���ʒu


						int taiou[10] = { 2,1,0,0,0,0 }; // �G���J�E���g0�Ԗڂ͓Gid2(�R�{���g)���o���A�̈Ӗ�

						for (int temp = 1; temp <= 2; temp = temp + 1) {
							if (xPosi == monPosiX[temp - 1] && yPosi == monPosiY[temp - 1] && toubouTyokugo[temp - 1] == 0) {

								// �����X�^�[�摜 // �f�o�b�O�p
								{
									mapEneNum = temp; //  2;// enemy_alive �ȂǂŎg��

									encount_monsters_id = taiou[temp - 1]; // �u���b�N�ŗL�̗v�f
									DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


								}


								battle_start();
								// mode_scene = MODE_BATTLE_COMMAND;

								DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
									GetColor(1, 1, 1), 1); // �����͍��w�i
								// window1Draw();
								DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�����X�^�[�����ꂽ"); // ������`�悷��




							}
						}
						if (!(xPosi == monPosiX[1 - 1] && yPosi == monPosiY[1 - 1])) {
							DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
								GetColor(1, 1, 1), 1); // �����͍��w�i
							// DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�e�X�g�p���b�Z�[�W"); // ������`�悷��

						}

					} // �����X�^�[��������




					// ���ɓ���̃G���J�E���g����
					{
						static int where_map = 1;
						check_encount_town();

					} // ���ɓ���̃G���J�E���g����


				}

				// if �c��ҋ@���[���ŁA�����X�{�^���������ꂽ��Athen ���j���[��ʂɑJ��

				CheckXetcFunc();
				if (CheckXetc) {
					// keyEnableX = 0;
					mode_scene = MODE_MENU;
					endX();

				}

				int infoX = 100; int infoY = 250;
				window1Draw(infoX, infoY, infoX + 150, infoY + 40 + 100);
				DrawFormatString(infoX, infoY, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��

			} // map ���[�h�̏I���



			// �^�E���̏���


			if (mode_scene == MODE_TOWN) {

				// MessageBox(NULL, TEXT("town�̃e�X�g���B"), TEXT("�L�[�e�X�g"), MB_OK);


				filterFlag = 1;

				// Draw_map(hdc);

				//window1Draw(winX1, winY1 + offsetY * j,	winX2, winY2 + offsetY * j);


				//BrushBlue_set(hdc);
				// Rectangle(hdc, 10, 10, 610, 80);

				//BrushPink_set(hdc);
				//	Rectangle(hdc, 10, 100,	300, 200);

				int mes1X = 220; int mes1Y = 140;
				window1Draw(mes1X, mes1Y, mes1X + 300, mes1Y + 30);

				lstrcpy(mojibuf, TEXT("�X�ɓ���܂����B�ǂ��֍s���܂���?"));
				// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));
				DrawFormatString(mes1X + 10, mes1Y + 10, GetColor(255, 255, 255), mojibuf); // ������`�悷��



				static int offsetYtemp1 = 100;
				// SelectObject(hdc, blue_thin_1);

				window1Draw(10, offsetYtemp1, 200, offsetYtemp1 + 300);

				// Rectangle(hdc, 10, offsetYtemp1,offsetYtemp1 + 100, 400);

				int carsoruHigh = 50; // �����X�p���ƃJ�[�\�������͓����ɂ��邱��

				// BrushPink_set(hdc);
				tenmetu(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1),
					150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1));

				// Rectangle(hdc, 20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1), 150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1));



				window1Draw(10, 80, 100, 120);

				static int offsetXtemp1 = 30; // �J�[�\�������Ɠ����Ȃ̂͋��R�B
				static int yspan1 = carsoruHigh;

				int temp = 0;

				struct localFuncStruct
				{
					void localText(int temp) {
						DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (temp), GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
				} localFunc;

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�s����"));
				//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (temp), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);


				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�M���h"));
				temp = 1;
				//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (1), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�h��"));
				temp = 2;
				// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (2), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("���X"));
				temp = 3;
				// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (3), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);


				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�o��"));
				temp = 4;
				// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (4), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);



				if (whomTargetID1 == 0) {
					lstrcpy(popMsg, TEXT("�p�[�e�B�̕Ґ����ł��܂��B"));
				}

				if (whomTargetID1 == 1 && afterShop == 0) {
					lstrcpy(popMsg, TEXT("HP��S�񕜂��܂��B"));
				}

				if (whomTargetID1 == 2 && afterShop == 0) {
					lstrcpy(popMsg, TEXT("�����i�⓹��̔������o���܂��B"));
				}

				if (whomTargetID1 == 3 && afterShop == 0) {
					lstrcpy(popMsg, TEXT("�X�̊O�ɏo�܂��B"));
				}


				if (popFlagTown == 1) {

					lstrcpy(mojibuf, TEXT("                                      "));

					mes1Y = 150 + 30;
					window1Draw(mes1X, mes1Y, mes1X + 300, mes1Y + 30);

					lstrcpy(mojibuf, popMsg);
					DrawFormatString(mes1X + 10, mes1Y + 10, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}

				// temp == tourokuNakama + 1    �ɑ���		
				// _stprintf_s(mojibuf, MAX_LENGTH, TEXT("�y�O���z"));		
				// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120, mojibuf, lstrlen(mojibuf));





				struct localFuncStruct2
				{
					void localExit() {
						townFlag = 1; // �^�E���ޏo�ɂ́A���ꂪ�K�v
						mode_scene = MODE_MAP;
						afterShop = 0;
					}
				} localFunc2;


				CheckXetcFunc();
				if (CheckXetc) {

					localFunc2.localExit();

					endX();
				}

				CheckZetcFunc();
				if (CheckZetc && whomTargetID1 == 3) {

					localFunc2.localExit();

					endZ();
				}



				// �\���L�[���͎�

				int rangeMin = 0; int rangeMax = 3;

				// �J�[�\������Ɉړ�
				{
					// �ړ��̏I������
					CheckUPetcFunc();
					if (CheckUPetc) {

						endUP();


						selecting_mainmenu--;     // ���1�}�X�����ړ�

						afterShop = 0;
					}
				}

				// �J�[�\�������Ɉړ�
				{
					// �ړ��̏I������
					CheckDOWNetcFunc();
					if (CheckDOWNetc) {

						endDOWN();

						selecting_mainmenu++;      // ����1�}�X�����ړ�

						afterShop = 0;
					}
				}

				// ���ʂ̌㏈��
				if (selecting_mainmenu < rangeMin) {
					selecting_mainmenu = rangeMin;
				}

				if (selecting_mainmenu >= rangeMax) {
					selecting_mainmenu = rangeMax;
				}

				whomTargetID1 = selecting_mainmenu;



				CheckZetcFunc();

				if (CheckZetc) {

					if (whomTargetID1 == 0) {


						// pre_guild(hWnd);

						Akihaikeisan();


						mode_scene = MODE_Guild_Main;

						endZ();
					}


					// �h
					if (whomTargetID1 == 1) {

						popFlagTown = 1;
						afterShop = 1;
						lstrcpy(popMsg, TEXT("�S�񕜂����B"));

						int tempYado; // for �Ŏg��
						// partyNinzuDone


						int aaaa = 0;

						for (aaaa = 0; aaaa <= partyNinzuDone - 1; aaaa = aaaa + 1) {

							tempYado = partyNarabijyun[aaaa];
							heros_def_list[tempYado].heros_hp = heros_def_list[tempYado].heros_hp_max;
							// heros_def_list[tempYado].heros_mp = heros_def_list[tempYado].heros_mp_max;

						}
					} // �h


					// ���X
					if (whomTargetID1 == 2) {

						// MessageBox(NULL, TEXT("�������B"), TEXT("�L�[�e�X�g"), MB_OK);

						whomTargetID1 = 0;
						whomCHARA = whomTargetID1 + 1;
						selecting_mainmenu = 0;


						endZ();
						mode_scene = MODE_Shop_Main;

					}

					if (whomTargetID1 == 3) {
						endZ();

						mode_scene = MODE_MAP;

					}
				}// check Z

			} // town


			if (mode_scene == MODE_Guild_Main) {
				filterFlag = 1;
				// Draw_map(hdc);

				// MessageBox(NULL, TEXT("�M���h�̃e�X�g���B"), TEXT("�L�[�e�X�g"), MB_OK);

				// BrushBlue_set(hdc);
				// Rectangle(hdc, 10, 10, 610, 80);

				// BrushPink_set(hdc);
				//	Rectangle(hdc, 10, 100,	300, 200);


				filterFlag = 1;

				hikaesai();
				parsai();



				lstrcpy(mojibuf, TEXT("�N�𒇊Ԃɂ��܂����H �I��ł��������B"));
				// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));
				DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				lstrcpy(mojibuf, TEXT("X�{�^���őޏo�B          "));
				// TextOut(hdc, 280, 350, mojibuf, lstrlen(mojibuf));
				DrawFormatString(280, 350, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				if (partyNinzuTemp <= 0) {

					lstrcpy(mojibuf, TEXT("�p�[�e�B�l����1�l�ȏ�K�v�ł��B"));
					//TextOut(hdc, 280, 350, mojibuf, lstrlen(mojibuf));

					DrawFormatString(280, 350, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}




				_stprintf_s(
					mojibuf, MAX_LENGTH, TEXT("%d"),
					partyNinzuDone);
				// TextOut(hdc, 280, 310, mojibuf, lstrlen(mojibuf));
				DrawFormatString(280, 310, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				CheckXetcFunc();
				if (CheckXetc) {
					//MessageBox(NULL, TEXT("X��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

					partyNinzuDone = partyNinzuTemp;
					mode_scene = MODE_TOWN;

					endX();
				}

				CheckZetcFunc();
				if (CheckZetc && whomCHARA == hikaeNinzu + 1) {
					//MessageBox(NULL, TEXT("X��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

					// keyHaijyo = 1;

					whomCHARA = hikaeNinzu; // �܂��u�O���v�ɂ����Ă�͖̂ʓ|�Ȃ̂� 1������B

					partyNinzuDone = partyNinzuTemp;

					whomCHARA = 0;
					mode_scene = MODE_Guild_Remove;

					endZ();
				}


				CheckZetcFunc();
				if (CheckZetc && whomCHARA != hikaeNinzu + 1) {


					if (uwadumeFlag == 0) {

						if (akikosuu >= 1 && whomCHARA - 1 <= tourokuNakama) {  // �p�[�e�B���̋󂫌�
						// �������̓p�[�e�B���̏㏑���p
							if (heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn == 0) {

								heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn = 1;

								// �d�l�ύX�ɂ��A���Ԃ�ς��Ă��o�O��Ȃ��B
								// ���L�̏�������邱�ƁE�E�E�������B���Ȃ��ƃo�O�������B
								partyNarabijyun[akiHairetu[0]] = whomCHARA - 1; // ��ɑ��
								// �l���̍X�V
								partyNinzuTemp = partyNinzuTemp + 1; // ���Ƃ���l�������Z
								hikaeNinzu = hikaeNinzu - 1;

								akiHairetu[0] = akiHairetu[1];

								uwagaki = 1;

								akikosuu = akikosuu - 1;


								endZ();

								mode_scene = MODE_Guild_Responce; // ���X�|���X���ɋ󂫔z��̌v�Z������̂Ŏc������


							}

						}

						if (akikosuu <= 0) {

							mode_scene = MODE_Guild_Main;


						}


						if (whomTargetID1hikae == tourokuNakama + 1) {
							// partyNinzuDone = partyNinzuDone -1;

							uwagaki = 1;

							whomCHARA = 0;

							mode_scene = MODE_Guild_Remove;
						}

					}



					if (uwadumeFlag == 1) {

						// �p�[�e�B��������ƍT���l�����ς��̂ŁA�ړ��惂�[�h����͐�ɍs���K�v����B
						if (whomCHARA == hikaeNinzu + 1) {

							uwagaki = 1;

							mode_scene = MODE_Guild_Remove;






							break; // ���L�̉������[�h��break�ŏȗ����Ȃ��ƍs���Ȃ��̂ŁA������break
						}


						// �ȉ��A���C�����[�h�B

						if (akikosuu >= 1 && whomCHARA - 1 <= tourokuNakama) {  // �p�[�e�B���̋󂫌�



						// �������̓p�[�e�B���̏㏑���p
							if (heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn == 0) {


								// MessageBox(NULL, TEXT("������33�B"), TEXT("�L�[�e�X�g"), MB_OK);


								heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn = 1;

								// �d�l�ύX�ɂ��A���Ԃ�ς��Ă��o�O��Ȃ��B
								// ���L�̏�������邱�ƁE�E�E�������B���Ȃ��ƃo�O�������B
								partyNarabijyun[akiHairetu[0]] = hikaeNarabijyun[whomCHARA - 1]; // ��ɑ��
								// �l���̍X�V
								partyNinzuTemp = partyNinzuTemp + 1; // ���Ƃ���l�������Z


								hikaeNinzu = hikaeNinzu - 1;



								akiHairetu[0] = akiHairetu[1];

								uwagaki = 1;

								akikosuu = akikosuu - 1;

								mode_scene = MODE_Guild_Responce; // ���X�|���X���ɋ󂫔z��̌v�Z������̂Ŏc������

							}
						}


						if (akikosuu <= 0) {
							// MessageBox(NULL, TEXT("������B"), TEXT("�L�[�e�X�g"), MB_OK);

							mode_scene = MODE_Guild_Main;


						}


						// �M���h�˓����ɂ��������Ă��邪�A�˓������͂����ł͕s�v�Ȃ̂ŁA�������ł��ʓr�A�����B
						// �T�������o�[���̃��X�g�`��
						hikaeKeisan();

					}


				}




				if (mode_scene == MODE_Guild_Main) { // remove���ɋ��ʓ���𕕂��邽��


					CheckUPetcFunc();
					if (CheckUPetc) {
						// MessageBox(NULL, TEXT("�オ������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
						whomCHARA = whomCHARA - 1;

						if (whomCHARA > hikaeNinzu) {
							whomCHARA = hikaeNinzu;
						}


						endUP();
					}


					CheckDOWNetcFunc();
					if (CheckDOWNetc) {



						// MessageBox(NULL, TEXT("����������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

						whomCHARA = whomCHARA + 1;

						if (whomCHARA > hikaeNinzu + 1) {
							whomCHARA = hikaeNinzu + 1;
						}

						endDOWN();

					}


					if (whomCHARA < 1) {
						whomCHARA = 1;
					}
					whomTargetID1 = whomCHARA - 1;

					beforeselect = whomCHARA;

					whomTargetID1hikae = whomTargetID1;

				}
			}


			if (mode_scene == MODE_Guild_Remove) {
				//BrushBlue_set(hdc);
				//BrushPink_set(hdc);

				hikaesai();
				parsai();


				CheckZetcFunc();
				if (CheckZetc) {
					//MessageBox(NULL, TEXT("X��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

					keyEnableZ = 0;
					partyNinzuTemp = partyNinzuTemp - 1;

					heros_def_list[partyNarabijyun[whomTargetID1party]].PartyIn = 0; // ��ɍT�����R�s�[���Ă���i���s�j
					partyNarabijyun[whomTargetID1party] = -1; // �p�[�e�B�����J���ɂ���B


					akikosuu = akikosuu + 1;


					Akihaikeisan();


					hikaeNinzu = hikaeNinzu + 1;

					// ���ꂪ�����
					hikaeKeisan();








					if (partyNinzuTemp >= 1) {



						int skip = 0;
						int kousinNarabijyun[partymax];

						partyNinzuDone = partyNinzuTemp;
						// MessageBox(NULL, TEXT("xxxxxxx��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);




						for (int temp = 0; temp < partymax; temp++)
						{
							if (partyNarabijyun[temp] >= 0) {
								kousinNarabijyun[temp - skip] = partyNarabijyun[temp];
							}

							if (partyNarabijyun[temp] < 0) {
								skip = skip + 1;
							}
						}

						for (int temp = 0; temp < partymax; temp++)
						{
							partyNarabijyun[temp] = kousinNarabijyun[temp];
						}

						//mode_scene = MODE_TOWN;

						//InvalidateRect(hWnd, NULL, FALSE);
						//UpdateWindow(hWnd);
					}


					mode_scene = MODE_Guild_Main;

					endZ();
				}





				CheckXetcFunc();
				if (CheckXetc) {
					//MessageBox(NULL, TEXT("X��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

					partyNinzuDone = partyNinzuTemp;
					mode_scene = MODE_Guild_Main;

					endX();
				}


				CheckUPetcFunc();
				CheckDOWNetcFunc();


				if (CheckUPetc || CheckDOWNetc) {

					if (CheckUPetc) {
						// MessageBox(NULL, TEXT("�オ������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
						whomCHARA = whomCHARA - 1;

						if (whomCHARA > partyNinzuTemp) {
							whomCHARA = partyNinzuTemp;
						}


						endUP();
					}


					if (CheckDOWNetc) {

						endDOWN();

						// MessageBox(NULL, TEXT("����������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

						whomCHARA = whomCHARA + 1;

						if (whomCHARA > partyNinzuTemp + 1) {
							whomCHARA = partyNinzuTemp + 1;
						}

					}

					// ���ʏ���
					if (whomCHARA < 1) {
						whomCHARA = 1;
					}
					whomTargetID1 = whomCHARA - 1;

					beforeselect = whomCHARA;

					whomTargetID1party = whomTargetID1;



				} // if ((CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1)


			}


			if (mode_scene == MODE_Guild_Responce) {

				// MessageBox(NULL, TEXT("�M���h�̃e�X�g���B"), TEXT("�L�[�e�X�g"), MB_OK);

				//BrushBlue_set(hdc);
				//BrushPink_set(hdc);

				lstrcpy(mojibuf, TEXT("�N�𒇊Ԃɂ��܂����H �I��ł��������B"));
				// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));
				DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				hikaesai();
				parsai();


				// �������㏑������Ă���B
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s �����Ԃɉ�������B"), heros_def_list[whomTargetID1hikae].heros_name);
				// TextOut(hdc, 280, 300, mojibuf, lstrlen(mojibuf));
				DrawFormatString(280, 300, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				lstrcpy(mojibuf, TEXT("X�{�^���őޏo�B"));
				// TextOut(hdc, 280, 350, mojibuf, lstrlen(mojibuf));

				DrawFormatString(280, 350, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				mode_scene = MODE_Guild_Main;
			}







			// if (mode_scene == MODE_Shop_Main && key_remain > 0) {



			if (mode_scene == MODE_Shop_Main) {
				filterFlag = 1;

				// Draw_map(hdc);

				//BrushBlue_set(hdc);
				// Rectangle(hdc, 10, 10, 610, 80);

				// BrushPink_set(hdc);
				//	Rectangle(hdc, 10, 100,	300, 200);

				shopCommon1();




				shopGoldRan();


				shopData();


				// �u����v�̂��ƂɁu�����v�����Ƃ��̕\�����̎c�[�̈�U�N���A�p
				for (int temp = 0; temp <= 6; temp = temp + 1) {
					lstrcpy(mojibuf, TEXT("   "));
					//TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
					//DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}


				int koumoku_Y = 200;
				int kasolOffsetY = 30;



				//shopCommand();

				shopHinBack();
				shopKoumoku();

				hinmokuView();









				lstrcpy(mojibuf, TEXT("���X�ɓ���܂����B�ǂ��֍s���܂���?"));
				//TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

				int XXX = 150; int YYY = 50;
				window1Draw(XXX - 10, YYY - 10, XXX + 300, YYY + 30);
				DrawFormatString(XXX, YYY, GetColor(255, 255, 255), mojibuf); // ������`�悷��





				if (popFlagTown == 1) {

					lstrcpy(mojibuf, TEXT("                                      "));
					// TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));

					//DrawFormatString(130, 150, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					lstrcpy(mojibuf, popMsg);
					//TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));


				}

				tempPass = whomTargetID1;






				// �\���L�[���͎�
				int rangeMin = 0; int rangeMax = 4;

				// �J�[�\������Ɉړ�
				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
						keyEnableUp = 0;
						nyuuryokuMatiUp = waitTime1;
						selecting_mainmenu--;     // ���1�}�X�����ړ�

					}


					if (selecting_mainmenu < rangeMin) {
						selecting_mainmenu = rangeMin;
					}

					if (selecting_mainmenu >= rangeMax) {
						selecting_mainmenu = rangeMax;
					}
				}

				// �J�[�\�������Ɉړ�
				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
						keyEnableDown = 0;
						nyuuryokuMatiDown = waitTime1;
						selecting_mainmenu++;                       // ����1�}�X�����ړ�
					}


					if (selecting_mainmenu < rangeMin) {
						selecting_mainmenu = rangeMin;
					}

					if (selecting_mainmenu >= rangeMax) {
						selecting_mainmenu = rangeMax;
					}

				}


				whomTargetID1 = selecting_mainmenu;

				if (whomTargetID1 == 0) {
					shopMijissou = 0;
					//mode_scene = MODE_Shop_weapon_main;
				}
				if (whomTargetID1 == 1) {
					shopMijissou = 0;
					//mode_scene = MODE_Shop_armor_main;
				}
				if (whomTargetID1 > 1) {
					shopMijissou = 1;
					//mode_scene = MODE_Shop_armor_main;
				}




				CheckXetcFunc();
				if (CheckXetc) {
					// keyEnableX = 0;
					mode_scene = MODE_TOWN;
					endX();

				}




				CheckZetcFunc();
				if (CheckZetc) {

					// buki
					if (whomTargetID1 == 0) {
						shopMijissou = 0;

						endZ();

						mode_scene = MODE_Shop_weapon_main;

					}


					// bougu
					if (whomTargetID1 == 1) {
						shopMijissou = 0;

						endZ();
						mode_scene = MODE_Shop_armor_main;

					} // �h


					// sousyoku
					if (whomTargetID1 == 2) {
						shopMijissou = 1;

						endZ();
						MessageBox(NULL, TEXT("�������B"), TEXT("�L�[�e�X�g"), MB_OK);

					}

					// dougu
					if (whomTargetID1 == 3) {
						shopMijissou = 1;

						endZ();
						MessageBox(NULL, TEXT("�������B"), TEXT("�L�[�e�X�g"), MB_OK);

					}


					if (whomTargetID1 == 4) {
						shopMijissou = 0;

						endZ();

						mode_scene = MODE_TOWN;

					}



				}// check Z




			} // shop






			if (mode_scene == MODE_Shop_weapon_main || mode_scene == MODE_Shop_armor_main) {
				filterFlag = 1;
				// Draw_map(hdc);

				// MessageBox(NULL, TEXT("�M���h�̃e�X�g���B"), TEXT("�L�[�e�X�g"), MB_OK);


				{
					//BrushDarkBlue_set(hdc);
					// Rectangle(hdc, 10, 10, 610, 80);

					// BrushDarkPink_set(hdc);
					//	Rectangle(hdc, 10, 100,	300, 200);


					lstrcpy(mojibuf, TEXT("���X�ɓ���܂����B�ǂ��֍s���܂���?"));
					// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

					//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					shopCommon1();

					int offsetXtemp1 = 30; // �J�[�\�������Ɠ����Ȃ̂͋��R�B
					int carsoruHigh = 30;
					int yspan1 = carsoruHigh;

					//DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (5), GetColor(255, 255, 255), mojibuf); // ������`�悷��



					// �\���L�[���͎�
					int rangeMin = 0; int rangeMax = 3;







				}



				if (popFlagTown == 1) {

					lstrcpy(mojibuf, TEXT("                                      "));
					// TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));

					DrawFormatString(130, 150, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					lstrcpy(mojibuf, popMsg);
					//TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));


				}



				//BrushBlue_set(hdc);
				//BrushPink_set(hdc);

				if (mode_scene == MODE_Shop_weapon_main) {
					//lstrcpy(mojibuf, TEXT("���퉮�e�X�g�B"));
				}
				if (mode_scene == MODE_Shop_armor_main) {
					//lstrcpy(mojibuf, TEXT("�h��e�X�g�B"));
				}
				//TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

				//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				shopAct = whomTargetID2;
				shopCommand();


				shopGoldRan();

				//shopKoumoku();


				int stypeOffset = soubiOffset - 1; //10;




					//BrushPink_set(hdc);


				// tenmetu(280, 200 + 60 + 30 * (whomTargetID4),				320 + 40, offsetYtemp1 + 60 + 60 + 30 * (whomTargetID4));









				shopData();

				// int stypeOffset = soubiOffset - 1; //10;
				int afterOffTemp = stypeOffset + 1;

				// int range;

				shopHinBack();
				shopKoumoku();

				hinmokuView();

				// �f�o�b�O�p
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), buyrange);
				DrawFormatString(280 + 100 * 3 + 50, koumoku_Y + 30 + kasolOffsetY * 5, GetColor(255, 255, 255), mojibuf); // ������`�悷��




				// �\���L�[���͎�
				int rangeMin = 0; int rangeMax = 4;


				// �J�[�\����migi�Ɉړ�
				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
						keyEnableLeft = 0;
						nyuuryokuMatiLeft = waitTime1;
						whomTargetID2--;     // ���1�}�X�����ړ�

					}


					if (whomTargetID2 < rangeMin) {
						whomTargetID2 = rangeMin;
					}

					if (whomTargetID2 >= rangeMax) {
						whomTargetID2 = rangeMax;
					}
				}

				// �J�[�\����hidari�Ɉړ�
				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {
						keyEnableRight = 0;
						nyuuryokuMatiRight = waitTime1;
						whomTargetID2++;                       // ����1�}�X�����ړ�
					}


					if (whomTargetID2 < rangeMin) {
						whomTargetID2 = rangeMin;
					}

					if (whomTargetID2 >= rangeMax) {
						whomTargetID2 = rangeMax;
					}

				}



				if (
					(CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1)
					||
					(CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1)
					) {


					//MessageBox(NULL, TEXT("�f�o�b�O�B"), TEXT("�e�X�g"), MB_OK);



					// �J�[�\����ue�Ɉړ�
						{

							// �ړ��̏I������
							if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
								keyEnableUp = 0;
								nyuuryokuMatiUp = waitTime1;



								whomTargetID1--;     // ���1�}�X�����ړ�

							}


							if (whomTargetID1 < rangeMin) {
								whomTargetID1 = rangeMin;
							}

							if (whomTargetID1 >= rangeMax) {
								whomTargetID1 = rangeMax;
							}
						}

						// �J�[�\����sita�Ɉړ�
						{

							// �ړ��̏I������
							if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
								keyEnableDown = 0;
								nyuuryokuMatiDown = waitTime1;
								whomTargetID1++;                       // ����1�}�X�����ړ�
							}


							if (whomTargetID1 < rangeMin) {
								whomTargetID1 = rangeMin;
							}

							if (whomTargetID1 >= rangeMax) {
								whomTargetID1 = rangeMax;
							}
						}


						if (whomTargetID1 == 0) {
							shopMijissou = 0;
							mode_scene = MODE_Shop_weapon_main;
						}
						if (whomTargetID1 == 1) {
							shopMijissou = 0;
							mode_scene = MODE_Shop_armor_main;
						}
						if (whomTargetID1 > 1) {
							shopMijissou = 1;
							mode_scene = MODE_Shop_armor_main;
						}


				} // ue or sita



				CheckZetcFunc();
				if (CheckZetc) {


					if (whomTargetID2 == 0) {
						endZ();

						if (mode_scene == MODE_Shop_weapon_main && shopMijissou == 0) {
							mode_scene = MODE_Shop_weapon_buy;
						}


						if (mode_scene == MODE_Shop_armor_main && shopMijissou == 0) {
							mode_scene = MODE_Shop_armor_buy;
						}


					}


					// sell
					if (whomTargetID2 == 1) {
						endZ();

						if (mode_scene == MODE_Shop_weapon_main) {
							mode_scene = MODE_Shop_weapon_sell;
						}
						if (mode_scene == MODE_Shop_armor_main) {
							mode_scene = MODE_Shop_armor_sell;
						}

					} // sell


					// ���X
					if (whomTargetID2 == 2) {
						endZ();

						if (mode_scene == MODE_Shop_weapon_main) {
							//mode_scene = MODE_Shop_weapon_buyOld;
						}
						if (mode_scene == MODE_Shop_armor_main) {
							//mode_scene = MODE_Shop_armor_buyOld ;
						}

					}

					if (whomTargetID2 == 3
						&&
						whomTargetID1 == 4

						) {

						endZ();

						mode_scene = MODE_TOWN;
						//	townFlag = 1; // �^�E���ޏo�ɂ́A���ꂪ�K�v
						//	mode_scene = MODE_MAP;

					}


					if (whomTargetID2 == 3
						&&
						whomTargetID1 != 4

						) {
						endZ();

						mode_scene = MODE_Shop_Main;

					}




				}// check Z


				CheckXetcFunc();
				if (CheckXetc) {
					// keyEnableX = 0;
					mode_scene = MODE_Shop_Main;
					endX();

				}

			}


			if (mode_scene == MODE_Shop_weapon_buy || (mode_scene == MODE_Shop_armor_buy)) {
				filterFlag = 1;
				//Draw_map(hdc);


				{
					int whomTargetID3 = tempPass;

					//BrushDarkBlue_set(hdc);
					// Rectangle(hdc, 10, 10, 610, 80);

					// BrushDarkPink_set(hdc);
					//	Rectangle(hdc, 10, 100,	300, 200);


					lstrcpy(mojibuf, TEXT("���X�ɓ���܂����B�ǂ��֍s���܂���?"));
					// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));


					//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��



					shopCommon1();
				}


				shopAct = 0;

				shopGoldRan();
				shopCommand();

				shopHinBack();
				shopKoumoku();





				//BrushPink_set(hdc);
				tenmetu(280, 200 + 60 + 30 * (whomTargetID4),
					320 + 40, offsetYtemp1 + 60 + 60 + 30 * (whomTargetID4));





				shopData();


				// �u����v�̂��ƂɁu�����v�����Ƃ��̕\�����̎c�[�̈�U�N���A�p
				for (int temp = 0; temp <= 6; temp = temp + 1) {
					lstrcpy(mojibuf, TEXT("   "));
					//TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
					DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��



				}


				hinmokuView();




				int koumoku_Y = 200;
				int kasolOffsetY = 30;




				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), buyrange);
				DrawFormatString(280 + 100 * 3 + 50, koumoku_Y + 30 + kasolOffsetY * 5, GetColor(255, 255, 255), mojibuf); // ������`�悷��



				CheckZetcFunc();
				if (CheckZetc) {

					int locType2 = itemTypeHairetu[whomTargetID4];
					// ��������
					if (your_money >= 50) {

						(soubiSyoji[itemHairetu[whomTargetID4]].Stype[locType2]).have_kosuu =
							(soubiSyoji[itemHairetu[whomTargetID4]].Stype[locType2]).have_kosuu + 1;

						// weapon_have_list[itemHairetu[whomTargetID1]].have_kosuu = weapon_have_list[itemHairetu[whomTargetID1]].have_kosuu + 1;
						your_money = your_money - 50;

					}
					// ���鏈��
					// ���蕨�Ȃ�


					endZ();

				}




















				CheckXetcFunc();
				if (CheckXetc) {
					// keyEnableX = 0;

					if (mode_scene == MODE_Shop_weapon_buy) {
						mode_scene = MODE_Shop_weapon_main;
					}
					if (mode_scene == MODE_Shop_armor_buy) {
						mode_scene = MODE_Shop_armor_main;
					}

					// mode_scene = MODE_Shop_Main;

					endX();

				}


				CheckUPetcFunc();
				if (CheckUPetc) {
					keyEnableUp = 0;
					nyuuryokuMatiUp = waitTime1;
					whomTargetID4 = whomTargetID4 - 1;

				}


				CheckDOWNetcFunc();
				if (CheckDOWNetc) {
					keyEnableDown = 0;
					nyuuryokuMatiDown = waitTime1;

					whomTargetID4 = whomTargetID4 + 1;

				}


				if (whomTargetID4 < 0) {
					whomTargetID4 = 0;

				}


				if (whomTargetID4 > buyrange) {
					whomTargetID4 = buyrange;

				}







			}


			if (mode_scene == MODE_Shop_weapon_sell || mode_scene == MODE_Shop_armor_sell) {
				filterFlag = 1;
				//Draw_map(hdc);



				{
					int whomTargetID3 = tempPass;

					//BrushDarkBlue_set(hdc);
					// Rectangle(hdc, 10, 10, 610, 80);

					//BrushDarkPink_set(hdc);
					//	Rectangle(hdc, 10, 100,	300, 200);


					lstrcpy(mojibuf, TEXT("���X�ɓ���܂����B�ǂ��֍s���܂���?"));
					// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

					//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					shopCommon1();

					// �\���L�[���͎�
					int rangeMin = 0; int rangeMax = 3;
				}





				shopCommand();

				shopHinBack();

				////////////// �����̃R�s�y�̋�


				int spanY = 30;
				int Y0 = 120;


				int itemskip = 0;
				goukeiItem = 0;

				int itemIDcount = 0;
				int column = 1; // 1�ɕύX

				int xcommon;
				int ycommon;


				// �A�C�e�������p
				itemskip = 0;
				int LimintTemp = goukeiItem;


				// �g�p�i�̔z����
				for (idTemp = 1; idTemp <= 3; idTemp = idTemp + 1)
				{

					if (item_have_list[idTemp].have_kosuu != 0) {

						goukeiItem = goukeiItem + 1;

						if (1) {
							itemHairetu[itemIDcount] = idTemp;
							itemTypeHairetu[itemIDcount] = siyouType;
							itemIDcount = itemIDcount + 1;
						}
					}

					if (item_have_list[idTemp].have_kosuu == 0 && idTemp != 3) {
						itemskip = itemskip + 1;

					}
				} // �g�p�i�̔z����



				itemskip = 0;
				LimintTemp = goukeiItem;

				//int locType2;

				// ����̔z����
				for (idTemp = 1; idTemp <= 2; idTemp = idTemp + 1)
				{
					if ((soubiSyoji[idTemp].Stype[wepoType]).have_kosuu != 0) {

						goukeiItem = goukeiItem + 1;

						if (1) {
							itemHairetu[itemIDcount] = idTemp;
							itemTypeHairetu[itemIDcount] = wepoType;
							itemIDcount = itemIDcount + 1;
						}
					}

					if ((soubiSyoji[idTemp].Stype[wepoType]).have_kosuu == 0 && idTemp != 2) {
						itemskip = itemskip + 1;

					}
				} // ����̔z����



				itemskip = 0;
				LimintTemp = goukeiItem;

				// �V�[���h�̔z����
				for (idTemp = 1; idTemp <= 2; idTemp = idTemp + 1)
				{
					if ((soubiSyoji[idTemp].Stype[tateType]).have_kosuu != 0) {
						// MessageBox(NULL, TEXT("�e�X�ghelm"), TEXT("�L�[�e�X�g"), MB_OK);

						goukeiItem = goukeiItem + 1;

						if (1) {
							itemHairetu[itemIDcount] = idTemp;
							itemTypeHairetu[itemIDcount] = tateType;
							itemIDcount = itemIDcount + 1;
						}

					}

					if ((soubiSyoji[idTemp - itemIDcount].Stype[tateType]).have_kosuu == 0) {
						//shield_have_list[idTemp - itemIDcount].have_kosuu == 0) {
						itemskip = itemskip + 1;

					}
				} // �V�[���h

				itemskip = 0;
				LimintTemp = goukeiItem;
				// �w�����̔z����
				for (idTemp = 1; idTemp <= 2; idTemp = idTemp + 1)
				{
					// MessageBox(NULL, TEXT("�e�X�g22"), TEXT("�L�[�e�X�g"), MB_OK);
					if ((soubiSyoji[idTemp].Stype[kabutoType]).have_kosuu != 0) {

						goukeiItem = goukeiItem + 1;

						if (1) {
							itemHairetu[itemIDcount] = idTemp;
							itemTypeHairetu[itemIDcount] = kabutoType;
							itemIDcount = itemIDcount + 1;
						}

					}

					if ((soubiSyoji[idTemp - itemIDcount].Stype[kabutoType]).have_kosuu == 0) {
						itemskip = itemskip + 1;

					}
				} // ���ԂƂ̔z����

				itemTypeHairetu[itemIDcount] = -99; // �I�����Ӗ����鐔�B


				//BrushPink_set(hdc);
				tenmetu(280, 200 + 60 + 30 * (whomTargetID4),
					320 + 40, offsetYtemp1 + 60 + 60 + 30 * (whomTargetID4));

				//SetBkColor(hdc, RGB(0xFF, 0xFF, 0xFF));
				//SetBkMode(hdc, OPAQUE);

				// ���o��
				shopKoumoku();


				// �y�[�W���莞�̈�U�N���A�p
				for (int temp = 0; temp <= 6; temp = temp + 1) {
					lstrcpy(mojibuf, TEXT("   "));
					// TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

					DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��



				}

				if (1) {
					for (int temp = 0; temp <= 10; temp = temp + 1) {


						int temp2 = temp + pageSyori * 6;

						if (itemTypeHairetu[temp2] == -99) {
							lstrcpy(mojibuf, TEXT("   "));
							//TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

							DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��


							break;
						}

						int locType2 = itemTypeHairetu[temp2]; // itemHairetu �ł͂Ȃ��B Type �Ȃ�


						if (itemTypeHairetu[temp2] == siyouType) {
							// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

							lstrcpy(mojibuf, item_def_list[itemHairetu[temp2]].def_name);
						}

						// else �����Ȃ��ƁA�Ȃ���siyouhin ������
						else if (itemTypeHairetu[temp2] == wepoType || tateType || kabutoType) {
							lstrcpy(mojibuf, (soubihin[itemHairetu[temp2]].Stype[locType2]).def_name);
						}


						// TextOut(hdc, 280, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
						DrawFormatString(280, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��


						lstrcpy(mojibuf, TEXT("50G"));
						// TextOut(hdc, 280 + 120, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

						DrawFormatString(280 + 120, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��



						// �����̔w�i�N���A�p
						lstrcpy(mojibuf, TEXT("   "));
						// TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

						DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��



						if (itemTypeHairetu[temp2] == siyouType) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), item_have_list[itemHairetu[temp2]].have_kosuu);

							//_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), itemTypeHairetu[temp2]);


						}

						// else �����Ȃ��ƁA�Ȃ���siyouhin ������
						else if (itemTypeHairetu[temp2] == wepoType || tateType || kabutoType) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[itemHairetu[temp2]].Stype[locType2]).have_kosuu);

							// _stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), itemTypeHairetu[temp2]);
							// lstrcpy(mojibuf, ( soubiSyoji[itemHairetu[temp2]].Stype[locType2]).have_kosuu);
						}



						// TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
						DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
				}





				CheckUPetcFunc();
				if (CheckUPetc) {
					keyEnableUp = 0;
					nyuuryokuMatiUp = waitTime1;
					whomTargetID4 = whomTargetID4 - 1;


					if (whomTargetID4 >= goukeiItem - 1) {
						whomTargetID4 = goukeiItem - 1;
					}

					else if ((pageSyori > 0) && (whomTargetID4 < 0)) {
						pageSyori = pageSyori - 1;
						whomTargetID4 = 5;
					}
					else if ((pageSyori == 0) && (whomTargetID4 < 0)) {
						pageSyori = 0;
						whomTargetID4 = 0;
					}

					if (goukeiItem <= 0) {
						// MessageBox(NULL, TEXT("�y�[�W�߂������̒����e�X�g"), TEXT("�L�[�e�X�g"), MB_OK);
						whomTargetID4 = 0;
					}



				}


				CheckDOWNetcFunc();
				if (CheckDOWNetc) {
					keyEnableDown = 0;
					nyuuryokuMatiDown = waitTime1;

					whomTargetID4 = whomTargetID4 + 1;

				}


				int temp2 = whomTargetID4 + pageSyori * 6;
				if (temp2 >= goukeiItem) {
					whomTargetID4 = whomTargetID4 - 1;
				}

				if (whomTargetID4 >= goukeiItem - 1) {
					whomTargetID4 = goukeiItem - 1;
				}
				else if (whomTargetID4 < 0) {
					whomTargetID4 = 0;
				}


				if (whomTargetID4 >= 6) {
					//MessageBox(NULL, TEXT("�y�[�W���菈���̒����e�X�g"), TEXT("�L�[�e�X�g"), MB_OK);
					pageSyori = 1;
					whomTargetID4 = 0;
				}

				if (goukeiItem <= 0) {
					// MessageBox(NULL, TEXT("�y�[�W���菈���̒����e�X�g"), TEXT("�L�[�e�X�g"), MB_OK);
					whomTargetID4 = 0;
				}







				CheckZetcFunc();
				if (CheckZetc) {


					int temp2 = whomTargetID4 + pageSyori * 6;

					// MessageBox(NULL, TEXT("�Ȃ����[�`��"), TEXT("�L�[�e�X�g"), MB_OK);
					// mode_scene = MODE_Shop_Main;

					sinamonoList = 1;
					// ���鏈��

					//if (your_money >= 50) {

					if (itemTypeHairetu[temp2] == siyouType) {
						item_have_list[itemHairetu[temp2]].have_kosuu = item_have_list[itemHairetu[temp2]].have_kosuu - 1;
						your_money = your_money + 50;
					}
					else {

						int locType2 = itemTypeHairetu[whomTargetID4];


						//
						(soubiSyoji[itemHairetu[whomTargetID4]].Stype[locType2]).have_kosuu =
							(soubiSyoji[itemHairetu[whomTargetID4]].Stype[locType2]).have_kosuu - 1;

						// weapon_have_list[itemHairetu[whomTargetID1]].have_kosuu = weapon_have_list[itemHairetu[whomTargetID1]].have_kosuu + 1;
						your_money = your_money + 50;
					}




					endZ();

				}



				CheckXetcFunc();
				if (CheckXetc) {
					// keyEnableX = 0;

					if (mode_scene == MODE_Shop_weapon_sell) {
						mode_scene = MODE_Shop_weapon_main;
					}
					if (mode_scene == MODE_Shop_armor_sell) {
						mode_scene = MODE_Shop_armor_main;
					}

					// mode_scene = MODE_Shop_Main;

					endX();

				}

			} // sell end



			if (mode_scene == MODE_BATTLE_COMMAND || mode_scene == MODE_BATTLE_COMMAND2 || mode_scene == MODE_BATTLE_MAGIC || mode_scene == MODE_BATTLE_NOW || mode_scene == MODE_BATTLE_WIN) {

				int monMesX = 400; int monMesY = 350; // ���b�Z�[�W���̕\���ʒu
				DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
					GetColor(1, 1, 1), 1);
				DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�����X�^�[�����ꂽ"); // ������`�悷��

				// �����X�^�[�摜 
				if (mode_scene == MODE_BATTLE_COMMAND || mode_scene == MODE_BATTLE_COMMAND2 || mode_scene == MODE_BATTLE_MAGIC || mode_scene == MODE_BATTLE_NOW) {

					{
						DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);
					}


				}


				// �G�֌W�̃p�����|�^�\��
				int monX = 450;
				int monY = 150;

				tekiTairetuAgility[0] = monster_def_list[encount_monsters_id - 1].mon_agility;


				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("HP %d"), monster_hp);
				DrawFormatString(monX, monY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), monster_name);
				DrawFormatString(monX, monY + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�f���� %d"), tekiTairetuAgility[0]);
				DrawFormatString(monX, monY + 20 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				int windowTempA = 410 + 100; // y �̈ʒu
				int chara_window_size_x = 140;

				// _itot_s(your_money , p,200, 10); // ����֐��Ȃ̂ŕۊ�

				int offsetBattleX = 170;
				int tempVAl;


				for (int iTemp = 0; iTemp <= partyNinzuDone - 1; iTemp++)
				{

					window1Draw(10 + iTemp * offsetBattleX, 350,
						10 + iTemp * offsetBattleX + 150, 470);

					tempVAl = partyNarabijyun[iTemp];


					/* �L�����̃X�e�[�^�X */
					DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 10,
						GetColor(255, 255, 255), heros_def_list[tempVAl].heros_name); // ������`�悷��


					lstrcpy(mojibuf, TEXT("HP"));
					DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[tempVAl].heros_hp);
					DrawFormatString(50 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[tempVAl].heros_hp_max);
					DrawFormatString(50 + 30 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					lstrcpy(mojibuf, TEXT("�f����"));
					DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40 + 30, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), sankaAgility[tempVAl]);
					DrawFormatString(50 + iTemp * offsetBattleX + 30, windowTempA - chara_window_size_x + 40 + 30, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}


				for (idTemp = 0; idTemp <= partyNinzuDone - 1; idTemp = idTemp + 1)
				{
					// �p�[�e�B�ɂ��Ȃ��L�������ƁA�ǂݎ��B
					// �p�[�e�B�L�����̒��o�́A��H���ōs���B
					mikataAgility[idTemp] = heros_def_list[idTemp].heros_agility;
				}


				// ����퓬�p�\�[�g
				for (idTemp = 0; idTemp <= partyNinzuDone - 1; idTemp = idTemp + 1)
				{
					// �����Ńp�[�e�B�L���������f�����𒊏o���Ă���BmikataAgi �͔�p�[�e�B�L�������܂�ł�̂ŁA���̍H�����K�v�B
					sankaAgility[idTemp] = mikataAgility[partyNarabijyun[idTemp]]; // sankaAgil �͂܂����ёւ��O

				}

				for (idTemp = 0; idTemp <= enemyNinzu - 1; idTemp = idTemp + 1)
				{
					sankaAgility[partyNinzuDone + idTemp] = tekiTairetuAgility[idTemp];

				}


				for (int loctempQ = 0; loctempQ <= partyNinzuDone + enemyNinzu - 1; ++loctempQ)
				{
					iremonoAgilityHairetu[loctempQ] = sankaAgility[loctempQ]; // iremonoAgi �� sanka �͓����e

					iremonoOrderHairetu[loctempQ] = loctempQ;
				} // �����l�̑��


				// �\�[�g�Ŏ���

				for (int loctempB = 0; loctempB <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1; ++loctempB)
				{
					for (int loctempA = loctempB; loctempA <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1; ++loctempA)
					{
						if (iremonoAgilityHairetu[loctempB] >= iremonoAgilityHairetu[loctempA + loctempB]) {

							// �������Ă��Ȃ�
						//	iremonoAgilityHairetu[loctempB] = iremonoAgilityHairetu[loctempB];
						//	iremonoAgilityHairetu[loctempA + loctempB] = iremonoAgilityHairetu[loctempA + loctempB];
							// ����p�ɏ�R�[�h2�s�͎c��

						}
						// locA�̂ق��������ł��B
						if (iremonoAgilityHairetu[loctempB] < iremonoAgilityHairetu[loctempA + loctempB]) {

							int tempSwapA, tempSwapB;

							tempSwapA = iremonoAgilityHairetu[loctempB];
							tempSwapB = iremonoAgilityHairetu[loctempA + loctempB];

							iremonoAgilityHairetu[loctempB] = tempSwapB;
							iremonoAgilityHairetu[loctempA + loctempB] = tempSwapA;


							int tempOrderSwapA, tempOrderSwapB;

							tempOrderSwapA = iremonoOrderHairetu[loctempB];
							tempOrderSwapB = iremonoOrderHairetu[loctempA + loctempB];

							iremonoOrderHairetu[loctempB] = tempOrderSwapB;
							iremonoOrderHairetu[loctempA + loctempB] = tempOrderSwapA;

							// �f�o�b�O���́uirem�v�ł͓��ꕨ�I�[�_�[�z��ł���B
						}
					}
				} // �����܂Ń\�[�g


				for (int loctempA = 0; loctempA <= partyNinzuDone - 1 + enemyNinzu; ++loctempA)
				{
					actionOrder[loctempA] = iremonoOrderHairetu[loctempA];
				}


				int mikataPE = 1; int tekiPE = 2;
				for (int loctempA = 0; loctempA <= partyNinzuDone - 1 + enemyNinzu; ++loctempA)
				{
					if (actionOrder[loctempA] <= partyNinzuDone - 1) {
						PorEflag[loctempA] = mikataPE;
						// actionOrder[loctempA] = actionOrder[loctempA];
					}

					if (actionOrder[loctempA] > partyNinzuDone - 1) {
						PorEflag[loctempA] = tekiPE;
						// actionOrder[loctempA] = -9;
					}

				}


				// �f�����z��̕\���e�X�g
				int agilityProcMonitorX = 370;
				int agilityProcMonitorY = 180;


				if (debugFlag == 1) {
					lstrcpy(mojibuf, TEXT("�f�����z��"));

					DrawFormatString(agilityProcMonitorX, agilityProcMonitorY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), iremonoAgilityHairetu[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
					// �퓬�f�o�b�O���̕`��v���O����


					// �s�����z��̕\���e�X�g 
					lstrcpy(mojibuf, TEXT("�s�����z��"));
					DrawFormatString(agilityProcMonitorX, agilityProcMonitorY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					lstrcpy(mojibuf, TEXT("irem"));
					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), iremonoOrderHairetu[tempMonitor]);
						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30, GetColor(255, 255, 255), mojibuf); // ������`�悷��
					}


					// �s�����z��̕\���e�X�g // ��������actionOrder
					lstrcpy(mojibuf, TEXT("act"));

					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("v%d"), actionOrder[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��
					}

					lstrcpy(mojibuf, TEXT("PE f"));

					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), PorEflag[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}

					lstrcpy(mojibuf, TEXT("Ac tp"));

					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 4, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), actionOrder[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 4, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
				} // �����܂Ńf�o�b�O��



				if (mode_scene == MODE_BATTLE_COMMAND) {
					int tem1X = 100; int Xwidth = 100;
					int tem1Y = 240;

					int yohakuY = 10;
					window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
						tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

					// �J�[�\��
					tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
						tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);


					int ComdTemp[5]; // �̂��̃^�[���J�nif���ŗ��p����̂Ŕz���`

					for (int temp = 0; temp <= 1; temp = temp + 1) {

						ComdTemp[temp] = temp;

						if (ComdTemp[temp] == 0) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("�키")); }
						if (ComdTemp[temp] == 1) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("������")); }

						DrawFormatString(tem1X + 20, tem1Y + 10 + 40 * ComdTemp[temp], GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}

					// �^�[���J�n of �키�R�}���h
					if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == ComdTemp[0] + 1 && keyHaijyo == 0
						// && mode_scene == MODE_BATTLE_COMMAND // ���ꂪ�����ƘA�łŃ^�[���ĊJ���Ă��܂� // ��L�R�}���h�ꗗ�Ɠ����̂��ߏ���
						) {

						// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

						TimeKasolCount = 10;

						keyHaijyo = 0;
						battlewait = 100;

						dameKei = 0;

						damage_EnemyAttack = 0;
						damage_HeroAttack = 0;

						selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] +1;
						mode_scene = MODE_BATTLE_COMMAND2;
						//mode_scene = MODE_BATTLE_NOW;

					} // �^�[���J�n of �키�R�}���h



					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 �́uwindowTempA�v

					// �f�o�b�O��
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("nmUP %d"), nyuuryokuMatiUp );
						DrawFormatString(battleMassBaseX + 200 + 80 * 1 , battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("keUP %d"), keyEnableUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 2 , battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("pag���� %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("partyNin %d"), partyNinzuDone); //sentouNaninme
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					} // �����܂Ńf�o��



				} //  MODE_BATTLE_COMMAND




				if (mode_scene == MODE_BATTLE_COMMAND2) {
					int tem1X = 100; int Xwidth = 100;
					int tem1Y = 240;

					int yohakuY = 10;
					window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
						tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

					// �J�[�\��
					tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
						tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);


					int ComdTemp[5]; // �̂��̃^�[���J�nif���ŗ��p����̂Ŕz���`

					for (int temp = 0; temp <= 1; temp = temp + 1) {

						ComdTemp[temp] = temp;

						if (ComdTemp[temp] == 0) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("�U��")); }
						if (ComdTemp[temp] == 1) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("���@")); }

						DrawFormatString(tem1X + 20, tem1Y + 10 + 40 * ComdTemp[temp], GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}

					_stprintf_s(mojibuf, TEXT("%s"), heros_def_list[sentouNaninme].heros_name ); //sentouNaninme

					DrawFormatString(tem1X + 100, tem1Y + 30 , GetColor(255, 255, 255), mojibuf); // ������`�悷��



					// �^�[���J�n of �키�R�}���h
					if (CheckHitKey(KEY_INPUT_Z) == 1 && keyHaijyo == 0 && TimeKasolCount > 20
						) {

						if (selecting_mainmenu == ComdTemp[0] + 1 ) {

							zenkaiBcKasol_1[sentouNaninme] = selecting_mainmenu -1;

							if (sentouNaninme >= partyNinzuDone-1) {
								// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

								TimeKasolCount = 0;

								keyHaijyo = 1;
								battlewait = 100;

								dameKei = 0;

								damage_EnemyAttack = 0;
								damage_HeroAttack = 0;

								
								koudouKiroku[sentouNaninme] = koudouAtk;

								mode_scene = MODE_BATTLE_NOW;
							}

							if (sentouNaninme < partyNinzuDone -1) {
								//MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);


								koudouKiroku[sentouNaninme] = koudouAtk;

								sentouNaninme = sentouNaninme + 1;
								TimeKasolCount = 0;

								
								selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] + 1;

								// selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] ;

							} // �^�[���J�n of �키�R�}���h							
						}


						else if (selecting_mainmenu == ComdTemp[0] + 2) {

							zenkaiBcKasol_1[sentouNaninme] = selecting_mainmenu -1;

							if (sentouNaninme < partyNinzuDone) {
								//MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);
								//sentouNaninme = sentouNaninme + 1;

								TimeKasolCount = 0;

								selecting_mainmenu = zenkaiBcKasol_2[sentouNaninme] + 1;
								mode_scene = MODE_BATTLE_MAGIC;
								koudouKiroku[sentouNaninme] = koudouMgk;
								magicAtkFlag[sentouNaninme] = 0;
							}

							if (sentouNaninme >= partyNinzuDone) {
								// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

								TimeKasolCount = 0;
							
								selecting_mainmenu = zenkaiBcKasol_2[sentouNaninme] + 1;
								mode_scene = MODE_BATTLE_MAGIC;
								koudouKiroku[sentouNaninme] = koudouMgk;
								magicAtkFlag[sentouNaninme] = 0;

								
							}
							// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);
						} // �^�[���J�n of �키�R�}���h
					} // z


					// �L�����Z��
					if (CheckHitKey(KEY_INPUT_X) == 1 && keyHaijyo == 0 && TimeKasolCount > 20
						// && mode_scene == MODE_BATTLE_COMMAND // ���ꂪ�����ƘA�łŃ^�[���ĊJ���Ă��܂� // ��L�R�}���h�ꗗ�Ɠ����̂��ߏ���
						) {

						if (sentouNaninme == 0) {
							// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

							TimeKasolCount = 20;

							keyHaijyo = 0;
							battlewait = 100;

							dameKei = 0;

							damage_EnemyAttack = 0;
							damage_HeroAttack = 0;

							selecting_mainmenu = 1;

							mode_scene = MODE_BATTLE_COMMAND;
							//mode_scene = MODE_BATTLE_NOW;
						}


						if (sentouNaninme > 0) {
							// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

							TimeKasolCount = 0;

							keyHaijyo = 0;
							battlewait = 100;

							dameKei = 0;

							damage_EnemyAttack = 0;
							damage_HeroAttack = 0;


							sentouNaninme = sentouNaninme - 1;
							//mode_scene = MODE_BATTLE_COMMAND;
							//mode_scene = MODE_BATTLE_NOW;
						}



					} // �L�����Z��


					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 �́uwindowTempA�v

					// �f�o�b�O��
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("nmUP %d"), nyuuryokuMatiUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 1, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("keUP %d"), keyEnableUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 2, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("pag���� %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("partyNin %d"), partyNinzuDone);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("sento %d"), sentouNaninme);
						DrawFormatString(battleMassBaseX + 200+150, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("zkB[sN] %d"), zenkaiBcKasol_1[sentouNaninme] );
						DrawFormatString(battleMassBaseX + 200 + 150, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("zkB2[sN] %d"), zenkaiBcKasol_2[sentouNaninme]);
						DrawFormatString(battleMassBaseX + 200 + 150, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��



						// zenkaiBcKasol_1[sentouNaninme]



					} // �����܂Ńf�o��

				} //  MODE_BATTLE_COMMAND2



				if (mode_scene == MODE_BATTLE_MAGIC) {
					int tem1X = 100; int Xwidth = 100;
					int tem1Y = 240;

					int yohakuY = 10;
					window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
						tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

					// �J�[�\��
					tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
						tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);


					int ComdTemp[5]; // �̂��̃^�[���J�nif���ŗ��p����̂Ŕz���`

					for (int temp = 0; temp <= 1; temp = temp + 1) {

						// magicList											
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), magic_def_list[temp].def_name);	

						ComdTemp[temp] = temp; // ��������ƕ\���ʒu���Y����̂Ŏc��
						DrawFormatString(tem1X + 20, tem1Y + 10 + 40 * ComdTemp[temp], GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}


					_stprintf_s(mojibuf, TEXT("%s"), heros_def_list[sentouNaninme].heros_name); //sentouNaninme

					DrawFormatString(tem1X + 100, tem1Y + 30, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					//MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

					// �^�[���J�n of �키�R�}���h
					if (CheckHitKey(KEY_INPUT_Z) == 1 && keyHaijyo == 0 && TimeKasolCount > 20	) {

						int magicTemp = (ComdTemp[0] + 1);

						if (selecting_mainmenu >= magicTemp  && selecting_mainmenu <= magicTemp + 1) {

							TimeKasolCount = 0;

							keyHaijyo = 0;
							battlewait = 100;

							dameKei = 0;

							damage_EnemyAttack = 0;
							damage_HeroAttack = 0;


							
							magicSel = selecting_mainmenu -(magicTemp);

							zenkaiBcKasol_2[sentouNaninme] = magicSel;

							if (sentouNaninme < partyNinzuDone) {

								
								magicKiroku[sentouNaninme] = magicSel;
								magicAtkFlag[sentouNaninme] = 1;

								//MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);
								sentouNaninme = sentouNaninme + 1;
								selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] + 1;

								keyHaijyo = 0;

								TimeKasolCount = 0;
								mode_scene = MODE_BATTLE_COMMAND2;

								
								
							}


							
							 if (sentouNaninme >= partyNinzuDone ) {
								//MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);
								//sentouNaninme = sentouNaninme + 1;

								keyHaijyo = 1;

								TimeKasolCount = 0;
								mode_scene = MODE_BATTLE_NOW;
								magicKiroku[sentouNaninme] = magicSel;
								magicAtkFlag[sentouNaninme] = 1;

								selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] + 1;
							}


						} // �^�[���J�n of �키�R�}���h


					}



					// �L�����Z��
					if (CheckHitKey(KEY_INPUT_X) == 1 && keyHaijyo == 0 && TimeKasolCount > 20	) {

						// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

						TimeKasolCount = 0;

						keyHaijyo = 0;
						battlewait = 100;

						dameKei = 0;

						damage_EnemyAttack = 0;
						damage_HeroAttack = 0;


						mode_scene = MODE_BATTLE_COMMAND2;
						//mode_scene = MODE_BATTLE_NOW;

					} // �^�[���J�n of �키�R�}���h


					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 �́uwindowTempA�v

					// �f�o�b�O��
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("nmUP %d"), nyuuryokuMatiUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 1, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("keUP %d"), keyEnableUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 2, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("pag���� %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(mojibuf, TEXT("partyNin %d"), partyNinzuDone);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // ������`�悷��




					} // �����܂Ńf�o��

					//MessageBox(NULL, TEXT("test�B"), TEXT("magic end �ꏊ�e�X�g"), MB_OK);

				} //  MODE_BATTLE_magic


				// �\���L�[���͎�
				if (keyHaijyo == 0) {
					// �J�[�\������Ɉړ�

					{

						// �ړ��̏I������
						CheckUPetcFunc();

						// if (CheckUPetc) {
						if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && nyuuryokuMatiUp <= 0) {
							endUP();

							// MessageBox(NULL, TEXT("��L�[2�e�X�g�B"), TEXT("�ꏊ�e�X�g"), MB_OK);


							selecting_mainmenu--;  // ���1�}�X�����ړ�
						}

						// ���l�������ɈႤ�̂ŁA���t�@�N�^���������
						if (selecting_mainmenu < 0) {
							selecting_mainmenu = 0;
						}

						if (selecting_mainmenu >= 3) {
							selecting_mainmenu = 3;
						}
					}


					// �J�[�\�������Ɉړ�
					{

						// �ړ��̏I������
						CheckDOWNetcFunc();
						if (CheckDOWNetc) {
							endDOWN();

							selecting_mainmenu++;                       // ����1�}�X�����ړ�
						}


						if (selecting_mainmenu < 1) {
							selecting_mainmenu = 1;
						}

						if (selecting_mainmenu >= 3) {
							selecting_mainmenu = 3;
						}

					}
				} //if (keyHaijyo == 0)


				battlewait = battlewait - 1;



				if (mode_scene == MODE_BATTLE_NOW) {

					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 �́uwindowTempA�v

					int pnCommon = partyNarabijyun[actionOrder[sentoKoudoCount]];



					// �f�o�b�O��
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						_stprintf_s(mojibuf, TEXT("pag���� %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						int pnCommon = partyNarabijyun[actionOrder[sentoKoudoCount]];
						_stprintf_s(mojibuf, TEXT("pnCommon %d"), pnCommon);
						DrawFormatString(battleMassBaseX + 200 + 150, battleMassBaseY + 50 * 4 - 40, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					} // �����܂Ńf�o��

					// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);




					if (actionOrder[sentoKoudoCount] <= partyNinzuDone - 1) {

						if (heros_def_list[pnCommon].heros_HP0_flag == 0) {

							_stprintf_s(mojibuf, TEXT("%s �̍U���I"), heros_def_list[pnCommon].heros_name);
							DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // ������`�悷��




						}
					}


					if (actionOrder[sentoKoudoCount] <= partyNinzuDone - 1) {

						if (heros_def_list[partyNarabijyun[actionOrder[sentoKoudoCount]]].heros_HP0_flag == 1) {


							_stprintf_s(mojibuf, TEXT("%s �͐퓬�s�\�œ����Ȃ�"), heros_def_list[partyNarabijyun[actionOrder[sentoKoudoCount]]].heros_name);
							DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						}
					}



					if (actionOrder[sentoKoudoCount] >= partyNinzuDone) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�G�̍U���I "));
						DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}



					// DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "�키�e�X�g"); // ������`�悷��

					if (PorEflag[sentoKoudoCount] == tekiPE) {
						if (encount_mons_alive == 1) {

							// enemy atack �Ł@tekidame =0 �ɂ���Ă�
							if (damepyon < 10 && tekidame == 0) {
								damepyon = damepyon + 1;
							}

							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d �_���[�W"), damage_EnemyAttack);
							DrawFormatString(30, 350 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						}
					}

					if (PorEflag[sentoKoudoCount] == mikataPE) {
						{
							// hero atack �Ł@tekidame =1 �ɂ���Ă�
							if (damepyon < 10 && tekidame == 1) {
								damepyon = damepyon + 1;
							}


							if (heros_def_list[partyNarabijyun[actionOrder[sentoKoudoCount]]].heros_HP0_flag == 0) {
								_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d �_���[�W"), damage_HeroAttack);
								DrawFormatString(monX + 10, monY - 30 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // ������`�悷��
							}

						}
					}

				}// now









				if (mode_scene == MODE_BATTLE_NOW && dameKei == 0) {

					if (PorEflag[sentoKoudoCount] == 1) {

						if (encount_mons_alive == 1) {
							heroside_attack();
							dameKei = 1;
						}
					}

					if (PorEflag[sentoKoudoCount] == tekiPE) {
						if (encount_mons_alive == 1) {

							enemy_attack();
							dameKei = 1;
						}
					}
				}

				// ���s����(sentoKoudoCount )���Z�b�g
				if (battlewait <= 0 && mode_scene == MODE_BATTLE_NOW && dameKei == 1) {
					battlewait = 0;
					dameKei = 0;

					if (monster_hp <= 0) {
						// MessageBox(NULL, TEXT("�G�|����3�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

						sentouNaninme = 0;
						mode_scene = MODE_BATTLE_WIN;
						battlewait = 60.0 * 2.0;

						// MessageBox(NULL, TEXT("�G�|�����B"), TEXT("�ꏊ�e�X�g"), MB_OK);
					}
					if (monster_hp > 0) {

						if (sentoKoudoCount <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 && dameKei == 0) {

							// MessageBox(NULL, TEXT("aaa"), TEXT("�ꏊ�e�X�g"), MB_OK);

							sentoKoudoCount = sentoKoudoCount + 1;
							battlewait = 60.0 * 2.0;
						}



						// �^�[���I��					
						if (sentoKoudoCount >= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 + 1) {

							// MessageBox(NULL, TEXT("qwerty"), TEXT("�ꏊ�e�X�g"), MB_OK);
							damage_EnemyAttack = 0;
							damage_HeroAttack = 0;

							sentoKoudoCount = 0;

							damepyon = 0;

							//
							sentouNaninme = 0;

							selecting_mainmenu = zenkaiBcKasol_1[0] +1;

//							selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme];

							mode_scene = MODE_BATTLE_COMMAND2;
						}
					}
					keyHaijyo = 0;
				} // battlewait ��0�̏��


				if (mode_scene == MODE_BATTLE_WIN) {

					// MessageBox(NULL, TEXT("�G�|�����B"), TEXT("�ꏊ�e�X�g"), MB_OK);

					if (partyNinzuDone <= 2) {
						DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "�|����"); // ������`�悷��
					}

					if (partyNinzuDone == 3) {
						DrawFormatString(monMesX + 100, 350 + 30, GetColor(255, 255, 255), "�|����"); // ������`�悷��
					}



					int senkaX = 250; int senkaY = 150;
					window1Draw(senkaX, senkaY, senkaX + 150, senkaY + 120);

					int offsetY2 = FontYoffset;
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Exp: %d"), monster_def_list[encount_monsters_id - 1].mon_exp);
					DrawFormatString(senkaX + 10, senkaY + offsetY2 * 1, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Gold: %d"), monster_def_list[encount_monsters_id - 1].mon_gold);
					DrawFormatString(senkaX + 10, senkaY + offsetY2 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					// debug you
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("mons id: %d"), encount_monsters_id);
					DrawFormatString(senkaX + 10, senkaY + offsetY2 * 3, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					keyHaijyo = 1; // �퓬�R�}���h�����s����Ȃ��悤�A�܂��r����

					toubouTyokugo[mapEneNum - 1] = 10; // �G�̕����܂Ŏc��10�J�E���g
					enemy_alive[mapEneNum - 1] = 0; // 0 ���ƓG�̎��S���̈Ӗ�


					if (battlewait <= 0 && senkaFlag == 0) {

						sentoKoudoCount = 0; // �^�[���I������

						// MessageBox(NULL, TEXT("�G�|�����B"), TEXT("�ꏊ�e�X�g"), MB_OK);

						// �J�l�ƌo���l�̍X�V
						your_money = your_money + monster_def_list[encount_monsters_id - 1].mon_gold;

						for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {

							// �o�^�L�����������ꍇ��z�肵�āi���jSLG�Ȃǁj�A�S�L�����͑������Ȃ��B							
							// MessageBox(NULL, TEXT("�G�|�����B"), TEXT("�ꏊ�e�X�g"), MB_OK);

							heros_def_list[partyNarabijyun[temp]].heros_exp = heros_def_list[partyNarabijyun[temp]].heros_exp + monster_def_list[encount_monsters_id - 1].mon_exp;

						}
						senkaFlag = 1;
					}


					if (CheckHitKey(KEY_INPUT_Z) == 1 && senkaFlag == 1) {
						sentoKoudoCount = 0; // �^�[���I��

						keyEnableReset();
						keyHaijyo = 0;
						mode_scene = MODE_MAP;// �e�X�g�p�ɓ|���������Ȃ̂�
						senkaFlag = 0; // ����Ȃ��ƁA�ȍ~�̐퓬�Ōo���l�Ȃǂ�����Ȃ��Ȃ�B
					}
				} // win



				// ������
				if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == 2 && keyHaijyo == 0 && mode_scene == MODE_BATTLE_COMMAND) {

					keyHaijyo = 1;

					TimeKasolCount = 0;
					// DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "������̂�1����");  // ����͎����b�Z�[�W�ŏ㏑������ď�����
					toubouSeikou = 1;
					toubouTyokugo[mapEneNum - 1] = 5;// �G�̕����܂Ŏc��5�J�E���g

				}

				if (toubouSeikou == 1) {
					DrawFormatString(monMesX +50, 350 + 30, GetColor(255, 255, 255), "������̂ɐ���"); // ��ʂɕ\�������̂́A������

				}

				if (toubouSeikou == 1 && TimeKasolCount == 60) {
					keyHaijyo = 0;
					mode_scene = MODE_MAP;
					toubouSeikou = 0; // ����Ȃ��ƍĐ펞�ɓ��S�������b�Z�[�W���o�Ă��܂� // ��������0�Z�b�g����ƁA���s�̂��тɃZ�b�g�ɂȂ�̂ŁA�������ŃZ�b�g
				}
			}


			if (mode_scene == MODE_MENU) {
				int HPX = 300; int HPY = 50;
				int shiftY = 80;
				// �E�B���h�E��

				if (partyNinzuDone < 3) {
					window1Draw(HPX, HPY, HPX + 150, HPY + 100 * 2);
				}

				if (partyNinzuDone >= 3) {
					window1Draw(HPX, HPY, HPX + 150, HPY + 80 * partyNinzuDone);
				}


				for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {
					DrawFormatString(HPX + 20, HPY + 20 * 0 + shiftY * temp, GetColor(255, 255, 255), "%s", heros_def_list[partyNarabijyun[temp]].heros_name); // ������`�悷��			
					DrawFormatString(HPX + 20, HPY + 20 * 1 + shiftY * temp, GetColor(255, 255, 255), "HP %d / %d", heros_def_list[partyNarabijyun[temp]].heros_hp, heros_def_list[partyNarabijyun[temp]].heros_hp_max); // ������`�悷��
					DrawFormatString(HPX + 20 * 3, HPY + 20 * 2 + shiftY * temp, GetColor(255, 255, 255), "EXP %d", heros_def_list[partyNarabijyun[temp]].heros_exp); // ������`�悷��

				}


				window1Draw(480, 380, 600, 470);
				DrawFormatString(500, 400, GetColor(255, 255, 255), "������"); // ������`�悷��
				DrawFormatString(500, 400 + 30, GetColor(255, 255, 255), "%d G", your_money); // ������`�悷��


				// �R�}���h�E�B���h�E�̊�ʒu
				int XXX = 100;  int YYY = 250;
				window1Draw(XXX, YYY, XXX + 150, YYY + 40 + 150);

				if (keyEnableX == 0) {

					DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "�J�E���g %d", nyuuryokuMatiX); // ������`�悷��
					nyuuryokuMatiX = nyuuryokuMatiX - 1;
				}

				if (nyuuryokuMatiX <= 0) {
					keyEnableX = 1;
					nyuuryokuMatiX = 0;

				}


				if (keyEnableX == 1) {
					// �_�ŃJ�[�\��				
					tenmetu(XXX, YYY + (selecting_mainmenu - 1) * 40, XXX + 80, YYY + (selecting_mainmenu - 1) * 40 + 40);


					// �R�}���h��			
					for (int j = 0; j <= 4; ++j) {

						// �����ɋ��ʂ���O�i�K�̍�Ƃ��L�q;

						// �񋤒�;
						if (j == 0) { lstrcpy(mojibuf, TEXT("����")); }
						if (j == 1) { lstrcpy(mojibuf, TEXT("����")); }
						if (j == 2) { lstrcpy(mojibuf, TEXT("�Z�\")); }
						if (j == 3) { lstrcpy(mojibuf, TEXT("�Z�[�u")); }
						if (j == 4) { lstrcpy(mojibuf, TEXT("���ёւ�")); }

						// �����ɋ��ʂ����i�K�̍�Ƃ��L�q;
						DrawFormatString(XXX + 20, YYY + 40 * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}


					// �\���L�[���͎�
					int rangeMin = 1; int rangeMax = 3;

					// �J�[�\������Ɉړ�
					{

						// �ړ��̏I������

						CheckUPetcFunc();
						if (CheckUPetc) {

							keyEnableUp = 0;
							nyuuryokuMatiUp = waitTime1;

							selecting_mainmenu--;     // ���1�}�X�����ړ�

						}


						if (selecting_mainmenu < rangeMin) {
							selecting_mainmenu = rangeMin;
						}

						if (selecting_mainmenu >= rangeMax) {
							selecting_mainmenu = rangeMax;
						}
					}


					// �J�[�\�������Ɉړ�
					{

						// �ړ��̉��~����
						CheckDOWNetcFunc();
						if (CheckDOWNetc) {

							keyEnableDown = 0;
							nyuuryokuMatiDown = waitTime1;

							selecting_mainmenu++;    // ����1�}�X�����ړ�
						}


						if (selecting_mainmenu < rangeMin) {
							selecting_mainmenu = rangeMin;
						}

						if (selecting_mainmenu >= rangeMax) {
							selecting_mainmenu = rangeMax;
						}
					}


					CheckZetcFunc();
					if (CheckZetc) {
						endZ();

						if (selecting_mainmenu == 1) {
							//mode_scene = itemModeMain;
							mode_scene = MODE_ITEM_TYPE;
							DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "�����I�т܂���������"); // ������`�悷��

							keyEnableReset();
						}

						if (selecting_mainmenu == 2) {
							mode_scene = MODE_EQUIP_MAIN;
							nyuuryokuMatiZ = waitTime1;

							DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "������I�т܂���������"); // ������`�悷��
							keyEnableReset();
						}


						if (selecting_mainmenu == 3) {
							MessageBox(NULL, TEXT("���Z���g�����߂̃R�}���h�i���������j�B"), TEXT("�e�X�g"), MB_OK);

							// ����̖����������Ȃ̂ŏ�����
							// mode_scene = MODE_SKILL_MAIN;

						}

						if (selecting_mainmenu == 4) {

							mode_scene = MODE_SAVE_MENU;


							// OP��ʂ̐ݒ�̃Z�[�u
							FILE* fp1;

							fp1 = fopen("OPSetting.txt", "w");
							{
								fprintf(fp1, "�j���[�Q�[�����ǂ���: %d \n", 2); // 2�Ȃ�u�Â�����v�ɐݒ�
							}
							fclose(fp1);


							// �Z�[�u�����
							// �Q�[�����f�[�^�̃Z�[�u
							FILE* fp2;
							{
								fp2 = fopen("savedata1.txt", "w");
								if ((fp2 = fopen("savedata1.txt", "w")) == NULL) {
									MessageBox(NULL, TEXT("�Z�[�u�����s���܂����B�Ώۃt�@�C�������݂��Ȃ��悤�ł��B"), TEXT("���b�Z�[�W"), MB_OK);
									break;
								}
								else {
									fprintf(fp2, "���݃}�b�v�ԍ�: %d \n", where_map);
									fprintf(fp2, "�L�����ʒux���W: %d \n", chara_x);
									fprintf(fp2, "�L�����ʒuy���W: %d \n", chara_y);


									fprintf(fp2, "�p�[�e�B�l��: %d \n", partyNinzuDone);
									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "�p�[�e�B %d �l�ڂ�ID: %d \n", temp + 1, partyNarabijyun[temp]);
									}

									fprintf(fp2, "�T���l��: %d \n", hikaeNinzu);
									for (int temp = 0; temp <= hikaeNinzu - 1; ++temp) {
										fprintf(fp2, "�T�� %d �l�ڂ�ID: %d \n", temp + 1, hikaeNarabijyun[temp]);
									}

									// ���[�h�̓s���ɂ��AHP��for�͍ő�HP��for�Ƃ͓������Ȃ����ƁB
									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "�p�[�e�B���L���� %d �Ԗڂ̌�HP: %d \n", temp + 1, heros_def_list[partyNarabijyun[temp]].heros_hp);
									}

									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "�p�[�e�B���L���� %d �Ԗڂ̍ő�HP: %d \n", temp + 1, heros_def_list[partyNarabijyun[temp]].heros_hp_max);
									}


									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "�p�[�e�B�L���� %d �Ԗڂ̕���: %d \n", temp + 1, weapon_def_list[
											heros_def_list[partyNarabijyun[temp]].heros_weapon1].def_id);
									}


									// �o�^���Ԃ̃p�����[�^�[�B�@�ꕔ�̓p�[�e�B�p���Əd������
									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "�o�^�L���� %d �Ԗڂ̌�HP: %d \n", temp + 1, heros_def_list[temp].heros_hp);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "�o�^�L���� %d �Ԗڂ̍ő�HP: %d \n", temp + 1, heros_def_list[temp].heros_hp_max);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "�o�^�L���� %d �Ԗڂ̕���: %d \n", temp + 1, weapon_def_list[
											heros_def_list[temp].heros_weapon1].def_id);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "�o�^�L���� %d �Ԗڂ̏�: %d \n", temp + 1, shield_def_list[
											heros_def_list[temp].heros_shield].def_id);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "�o�^�L���� %d �Ԗڂ̊�: %d \n", temp + 1, helm_def_list[
											heros_def_list[temp].heros_helm].def_id);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "�o�^�L���� %d �Ԗڂ̌o���l: %d \n", temp + 1, heros_def_list[temp].heros_exp);
									}


									fprintf(fp2, "������: %d G\n", your_money);

									char aaa[100];

									// �A�C�e���ނ̏�����


									// �g�p�i�̏�����
									for (int temp = 0; temp <= 3 - 1; ++temp) {

										//WideCharToMultiByte(CP_ACP, 0, item_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL); // ����֐����R�s�y�p�ɕۊ�
										fprintf(fp2, "%s �̌�: %d \n", aaa, item_have_list[temp].have_kosuu);
									}

									// �����i�̕���̏�����
									for (int temp = 0; temp <= 3 - 1; ++temp) {
										fprintf(fp2, "%s �̌�: %d \n", aaa, weapon_have_list[temp].have_kosuu);
									}

									// �����i�̏��̏�����
									for (int temp = 0; temp <= 3 - 1; ++temp) {
										fprintf(fp2, "%s �̌�: %d \n", aaa, shield_have_list[temp].have_kosuu);
									}

									// �����i�̃J�u�g�̏�����
									for (int temp = 0; temp <= 3 - 1; ++temp) {
										fprintf(fp2, "%s �̌�: %d \n", aaa, helm_have_list[temp].have_kosuu);
									}

									fclose(fp2);
								}
							}

							TimeCount = 0;
							mode_scene = MODE_saving_Now; // �Z�[�u�I����Ƀ^�C�}�[�ł��΂炭�\���B
							// MessageBox(NULL, TEXT("���܂���"), TEXT("���b�Z�[�W"), MB_OK);
						}

						if (selecting_mainmenu == 5) {
							// MessageBox(NULL, TEXT("���ёւ������邽�߂̃R�}���h�i���������j�B"), TEXT("�e�X�g"), MB_OK);

							for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {
								partyNarabijyunBefore[temp] = partyNarabijyun[temp];
								partyNarabijyunAfter[temp] = partyNarabijyun[temp];
							}

							whomTargetID1 = 0;
							mode_scene = MODE_narabikae_select1;
						}
					}
				}

				if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
					mode_scene = MODE_MAP;

					keyEnableReset();
				}
			} // menu �̏I���


			if (mode_scene == MODE_ITEM_TYPE) {

				window1Draw(10, 10, 610, 80);

				if (mode_scene != MODE_ITEM_TYPE) {

					tenmetu(20 + (selecting_mainmenu - 1) * 100, 20,
						100 + (selecting_mainmenu - 1) * 100, 70);
				}

				if (mode_scene == MODE_ITEM_TYPE) {

					tenmetu(20 + (selecting_mainmenu - 1) * (100 + 10), 20 + 20,
						100 + (selecting_mainmenu - 1) * (100 + 10), 70);
				}


				// ����`�Z�[�u �̃��j���[��
				int	menuComBaseX = 20; int menuComOffsetPerX = 100;
				int menuComBaseY = 20;

				if (mode_scene == MODE_ITEM_TYPE) {

					for (int j = 0; j <= 2; ++j) {

						// �񋤒�;
						if (j == 0) { lstrcpy(mojibuf, TEXT("���Օi")); }
						if (j == 1) { lstrcpy(mojibuf, TEXT("�����i")); }
						if (j == 2) { lstrcpy(mojibuf, TEXT("�厖�Ȃ���")); }

						// �����ɋ��ʂ����i�K�̍�Ƃ��L�q;

						DrawFormatString(menuComBaseX + (menuComOffsetPerX + 10) * j, menuComBaseY + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
				}


				if (mode_scene == MODE_MENU || mode_scene == MODE_ITEM_TYPE) {

					/* �������̕\���� */

					window1Draw(500, 250, 600, 350);

					int GoldViewBaseX = 510; int GoldViewBaseY = 260;

					lstrcpy(mojibuf, TEXT("������"));
					DrawFormatString(GoldViewBaseX, GoldViewBaseY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d G"), your_money);
					DrawFormatString(GoldViewBaseX, GoldViewBaseY + 40, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					// _itot_s(your_money , p,200, 10); // ����֐��Ȃ̂ŃR�s�y�p�Ɏc��


					/* �L�����̃X�e�[�^�X�� */
					menu_CharaSelectDraw2();

				}


				// ����`�Z�[�u �̃��j���[��
				int XXX = 100;  int YYY = 250;

				int darkWinX = 10; int darkWinY = 250;
				tekidame = 0;

				if (damepyon <= XXX && tekidame == 0) {
					damepyon = damepyon + 5;
				}

				darkwindow1Draw(darkWinX + XXX - damepyon, darkWinY, darkWinX + 110 + XXX - damepyon, darkWinY + 200);
				tenmetuStop(darkWinX, darkWinY, darkWinX + 110, darkWinY + 30);


				for (int j = 0; j <= 4; ++j) {

					// �����ɋ��ʂ���O�i�K�̍�Ƃ��L�q;

					// �񋤒�;
					if (j == 0) { lstrcpy(mojibuf, TEXT("����")); }
					if (j == 1) { lstrcpy(mojibuf, TEXT("����")); }
					if (j == 2) { lstrcpy(mojibuf, TEXT("�Z�\")); }
					if (j == 3) { lstrcpy(mojibuf, TEXT("�Z�[�u")); }
					if (j == 4) { lstrcpy(mojibuf, TEXT("���ёւ�")); }

					// �����ɋ��ʂ����i�K�̍�Ƃ��L�q;
					DrawFormatString(darkWinX + 20, darkWinY + 40 * j, GetColor(255 * 2 / 3, 255 * 2 / 3, 255 * 2 / 3), mojibuf); // ������`�悷��

				}


				if (mode_scene == MODE_ITEM_TYPE) {
					itemList(soubihin, soubiSyoji, 0);

				} // itemlist


				if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {


					if (selecting_mainmenu == 1) {
						// MessageBox(NULL, TEXT("���Օi�Ƃ��B"), TEXT("�L�[�e�X�g"), MB_OK);

						selecting_item = 1;
						selecting_item_x = ((selecting_item - 1) % 2) + 1;
						selecting_item_y = ((selecting_item - 1) / 2) + 1;

						mode_scene = MODE_ITEM_MENU; // MODE_ITEM_MENU;

					}


					if (selecting_mainmenu == 2) {
						// MessageBox(NULL, TEXT("�����i�̊m�F�B�������B�����R�}���h�Ƃ͕�"), TEXT("�e�X�g"), MB_OK);
						selecting_item = 1;
						selecting_item_x = ((selecting_item - 1) % 2) + 1;
						selecting_item_y = ((selecting_item - 1) / 2) + 1;


						mode_scene = MODE_ITEMweapon_MENU;
					}


					if (selecting_mainmenu == 3) {
						MessageBox(NULL, TEXT("�厖�Ȃ��́i���������j�B"), TEXT("�e�X�g"), MB_OK);

					}

					keyEnableReset();
				}

				CheckXetcFunc();
				if (CheckXetc) {

					{
						key_remain = 0;
						damepyon = 0;

						mode_scene = MODE_MENU;

						endX();
					}
					keyEnableUp = 0;

					keyEnableDown = 0;

					kasol2Target = 0;
					selecting_mainmenu = 1;
				}


				int itemTypeMax = 3;
				// �J�[�\�������Ɉړ�
				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
						keyEnableLeft = 0;
						nyuuryokuMatiLeft = waitTime1;
						selecting_mainmenu--;      // ���1�}�X�����ړ�

					}


					if (selecting_mainmenu < 0) {
						selecting_mainmenu = 0;
					}

					if (selecting_mainmenu >= itemTypeMax) {
						selecting_mainmenu = itemTypeMax;
					}
				}


				// �J�[�\����migi �Ɉړ�
				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {

						// MessageBox(NULL, TEXT("�厖�Ȃ��́i���������j�B"), TEXT("�e�X�g"), MB_OK);

						keyEnableRight = 0;
						nyuuryokuMatiRight = waitTime1;

						selecting_mainmenu++;     // ����1�}�X�����ړ�
					}


					if (selecting_mainmenu < 1) {
						selecting_mainmenu = 1;
					}

					if (selecting_mainmenu >= itemTypeMax) {
						selecting_mainmenu = itemTypeMax;
					}

				}
			}


			if (mode_scene == MODE_ITEM_WHOM) {

				darkFlag = 1;
				darkFlag = 0;

				// �����܂ŁA�w�i�t�B���^�[�ŉB�����B

				// Graphics �^�̖��߂̓ǂݍ��݂̂��߂Ƀ_�~�[�ϐ� graphics ��錾.
				//Graphics graphics(hdc);

				// �摜�̕`��B �_�~�[�ϐ� graphics �𒇉�ĕ`�悷��K�v������.
				//graphics.DrawImage(&image1, 0, 0, image1.GetWidth(), image1.GetHeight());

				// �摜�̓ǂݍ��݁uimage2�v�͕ϐ����B���ꂪ�w�i�t�B���^�[�B
				if (filterFlag == 0) {

					//Image image2(L"filter.png");

					// �摜�̕`��B �_�~�[�ϐ� graphics �𒇉�ĕ`�悷��K�v������.

					//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
					filterFlag = 1;
				}

				menu_CharaSelectDraw();
			}





			if (mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) {

				itemList(soubihin, soubiSyoji, 1);
			} // end


			// �������̓{�^������
			if ((mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) && key_remain > 0) {


				if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

					whatuse = itemHairetu[selecting_item - 1]; //

					key_remain = 0;

					int tempItemPro = 0;
					if (whatuse == -99) {
						tempItemPro = 1;
						// break; // 	DX���C�u�������ƃA�v���I�����ۂ��̂ŃR�����g�A�E�g	
					}

					if (mode_scene == MODE_ITEM_MENU && tempItemPro == 0) {
						mode_scene = MODE_ITEM_WHOM; // 		
					}

					endZ2();
				}


				if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
					//MessageBox(NULL, TEXT("X��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

					mode_scene = MODE_ITEM_TYPE;

					endX();
				}


				// �J�[�\������Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					CheckUPetcFunc();

					if (CheckUPetc) {
						endUP();

						// �ʂ̏���
						if (itemHairetu[1] == -99) {
							MessageBox(NULL, TEXT("ue��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
							// break; //
						}
						selecting_item = selecting_item - 2; // �������ƂɈႤ

						// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱�� if���̊O�ɏo���Ȃ��̂�
						item_select();
						//moving = 0;

						//MessageBox(NULL, TEXT("ue��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

					}
				}


				// �J�[�\�������Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					CheckDOWNetcFunc();
					if (CheckDOWNetc) {
						endDOWN();

						// �ʂ̏���

						if (itemHairetu[1] == -99) {
							MessageBox(NULL, TEXT("sita��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
							// break; //
						}
						selecting_item = selecting_item + 2; // �������ƂɈႤ

						// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱��
						item_select();
						//moving = 0;
						//MessageBox(NULL, TEXT("sita��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
					}
				}


				// �J�[�\�����E�Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {
						keyEnableRight = 0;

						nyuuryokuMatiLR = waitTime1;
						nyuuryokuMatiLeft = waitTime1;
						nyuuryokuMatiRight = waitTime1;

						//
						if (itemHairetu[1] == -99) {
							//break; //
						}
						selecting_item = selecting_item + 1; // �������ƂɈႤ

						// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱��
						item_select();
						//moving = 0;
					}

				}

				// �J�[�\�������Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
						keyEnableLeft = 0;

						nyuuryokuMatiLR = waitTime1;
						nyuuryokuMatiLeft = waitTime1;
						nyuuryokuMatiRight = waitTime1;

						//
						if (itemHairetu[1] == -99) {
							//break; //
						}
						selecting_item = selecting_item - 1; // �������ƂɈႤ

						// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱��
						item_select();
						//moving = 0;
					}
				}

			}


			if (mode_scene == MODE_ITEM_WHOM) {
				if (healflag == 1) {
					waitheal = waitheal - 1;
				}
				if (waitheal <= 100 && waitheal > 0) {

					waitheal = waitheal - 1;
					healflag = 2; // �\���֐��Ŏg���̂Ŏc���Ă�������
				}
				if (waitheal <= 0 && healflag != 0) {
					// MessageBox(NULL, TEXT("�e�X�g"), TEXT("�L�[�e�X�g"), MB_OK);
					waitheal = 0;
					healflag = 0;
				}


				int tempVal;

				if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && key_remain == 1) {

					//MessageBox(NULL, TEXT("���܃R�R1"), TEXT("���b�Z�[�W"), MB_OK);
					keyEnableReset();

					key_remain = 0;
					whomTargetID1 = whomCHARA - 1;
					item_have_list[0].have_kosuu = 0;

					// �����̓A�C�e���g�p���̌���

					// �򑐂̌���
					if (whatuse == 1) {
						//MessageBox(NULL, TEXT("���܃R�R1"), TEXT("���b�Z�[�W"), MB_OK);		
					}


					// �ŏ����̌���
					if (whatuse == 2) {

					}


					// �s�����̔��̌���
					if (whatuse == 3) {
						heros_def_list[partyNarabijyun[whomTargetID1]].heros_HP0_flag = 0;

					}


					// �񕜂̋��ʏ���
					if (item_have_list[whatuse].have_kosuu > 0) {

						tempVal = partyNarabijyun[whomTargetID1];

						if (heros_def_list[tempVal].heros_hp < heros_def_list[tempVal].heros_hp_max) {
							item_have_list[whatuse].have_kosuu = item_have_list[whatuse].have_kosuu - 1;



							healflag = 1; waitheal = 120;


							healkioku = partyNarabijyun[whomTargetID1];
						}

						healti = item_def_list[whatuse].healti;
						heros_def_list[tempVal].heros_hp = heros_def_list[tempVal].heros_hp + healti;

					}

					// ���ʏ��� ���[���Ȃ̂Ɍ���{�^������������A�A�C�e���I���ɖ߂�
					if (item_have_list[whatuse].have_kosuu <= 0) {
						mode_scene = MODE_ITEM_MENU;

						//break; // ������ƁA�Ȃ��������I���Ȃ̂ŁA�R�����g�A�E�g
					}

					// ���ʏ��� ���ʂ̒��ߕ����J�b�g
					if (item_have_list[whatuse].have_kosuu > 0) {


						if (heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp > heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp_max) {
							heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[whomTargetID1].heros_hp_max;
						}


					}


					// ���ʏ��� ��
					if (item_have_list[whatuse].have_kosuu <= 0) {
						item_have_list[whatuse].have_kosuu = 0;
					}

					nyuuryokuMatiX = waitTime1;
					nyuuryokuMatiZ = waitTime1;
				} // if (CheckHitKey(KEY_INPUT_Z) == 1


				if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0) {
					// MessageBox(NULL, TEXT("X��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
					keyEnableReset();


					filterFlag = 0;
					mode_scene = MODE_ITEM_MENU;

					nyuuryokuMatiX = waitTime1;
					nyuuryokuMatiZ = waitTime1;

				}


				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
					// MessageBox(NULL, TEXT("�オ������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
					whomCHARA = whomCHARA - 1;

					if (whomCHARA > partyNinzuDone) {
						whomCHARA = partyNinzuDone;
					}
					else if (whomCHARA < 1) {
						whomCHARA = 1;
					}
					whomTargetID1 = whomCHARA - 1;

					beforeselect = whomCHARA;
				}


				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
					// MessageBox(NULL, TEXT("����������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);
					whomCHARA = whomCHARA + 1;

					if (whomCHARA >= partyNinzuDone) {
						whomCHARA = partyNinzuDone;
					}
					else if (whomCHARA < 1) {
						whomCHARA = 1;
					}
					whomTargetID1 = whomCHARA - 1;

					beforeselect = whomCHARA;
				}

			} // �A�C�e���Ώێ҃t�����g�̏I���


			if (mode_scene == MODE_EQUIP_MAIN) {

				// �O���t�B�b�N�֌W
				{
					// �����̕\����
					// ���C�����[�h�͑����L�����̑I�����[�h�ł���

					int StatsHPbaseX = 130;
					int StatsHPbaseY = 130;
					int offsetY = 120;

					// �w�i�̐�

					window1Draw(10, 350, 500, 400);

					lstrcpy(mojibuf,
						TEXT("������ύX����L������I��ł��������B"));

					DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // ������`�悷��


					for (int j = 0; j <= partyNinzuDone - 1; ++j) {
						// �w�i�̐�

						window1Draw(10, 100 + offsetY * j, 300, 200 + offsetY * j);

						// �J�[�\��
						if (whomTargetID1 == j) {

							tenmetu(10, 100 + offsetY * (whomTargetID1),
								300, 200 + offsetY * (whomTargetID1));

						}

						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("%s"),
							heros_def_list[partyNarabijyun[j]].heros_name);

						DrawFormatString(StatsHPbaseX,
							StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						lstrcpy(mojibuf, TEXT("HP"));
						DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("%d"),
							heros_def_list[partyNarabijyun[j]].heros_hp);

						DrawFormatString(StatsHPbaseX + 30,
							StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("/ %d"),
							heros_def_list[partyNarabijyun[j]].heros_hp_max);

						DrawFormatString(StatsHPbaseX + 30 * 2,
							StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("%d"),
							heros_def_list[partyNarabijyun[j]].heros_HP0_flag);

						DrawFormatString(StatsHPbaseX,
							StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


						if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�퓬�s�\"));

							DrawFormatString(StatsHPbaseX,
								StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						}

						if (debugFlag == 1) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("mode: %d"), mode_scene);
							DrawFormatString(130 * 2, 300, GetColor(255, 255, 255), mojibuf); // ������`�悷��
						}
					}

					// ���̃L�����̑������ڂ̑I�����T�u���[�h

				}// �O���t�B�b�N�֌W

				if (keyEnableZ == 0 && nyuuryokuMatiZ >= 0) {
					nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				}

				if (keyEnableZ == 0 && nyuuryokuMatiZ <= 0) {
					keyEnableZ = 1;

					// �f�o�b�O�p
					// MessageBox(NULL, TEXT("�����ɂ���B"), TEXT("�L�[�e�X�g"), MB_OK);
				}

				CheckZetcFunc();
				if (CheckZetc) {

					key_remain = 0;
					whomTargetID1 = whomCHARA - 1;

					mode_scene = MODE_EQUIP_EDIT;
					beforeselect = 0;
					keyEnableReset();
				}


				if (nyuuryokuMatiX > 0) {
					nyuuryokuMatiX = nyuuryokuMatiX - 1;

				}

				if (keyEnableX == 0 && nyuuryokuMatiX <= 0) {
					nyuuryokuMatiX = 0;
					keyEnableX = 1;

				}

				CheckXetcFunc();
				if (CheckXetc) {

					filterFlag = 0;
					mode_scene = MODE_MENU;

					endX();
				}


				CheckUPetcFunc();
				if (CheckUPetc) {

					// MessageBox(NULL, TEXT("�オ������܂����B"),
				// TEXT("�L�[�e�X�g"), MB_OK);
					whomCHARA = whomCHARA - 1;

					if (whomCHARA > partyNinzuDone) {
						whomCHARA = partyNinzuDone;
					}
					else if (whomCHARA < 1) {
						whomCHARA = 1;
					}
					whomTargetID1 = whomCHARA - 1;


					beforeselect = whomCHARA;
				}


				CheckDOWNetcFunc();
				if (CheckDOWNetc) {

					// MessageBox(NULL, TEXT("����������܂����B"),
					// TEXT("�L�[�e�X�g"), MB_OK);
					whomCHARA = whomCHARA + 1;

					if (whomCHARA >= partyNinzuDone) {
						whomCHARA = partyNinzuDone;
					}
					else if (whomCHARA < 1) {
						whomCHARA = 1;
					}
					whomTargetID1 = whomCHARA - 1;


					beforeselect = whomCHARA;
				}

			} // equip ���[�h�̏I���



			if (mode_scene == MODE_EQUIP_EDIT || mode_scene == MODE_EQUIP_EDIT2) {
				// �����̕\����
				// ���C�����[�h�͑����L�����̑I�����[�h�ł���
				// MessageBox(NULL, TEXT("aaaa�R�R1"), TEXT("���b�Z�[�W"), MB_OK);


				const int StatsHPbaseX = 130;
				const int StatsHPbaseY = 130;
				int offsetY = 120;


				// �w�i�̐�
				window1Draw(10, 100, 350, 300 + 40);

				// �J�[�\��
				if (mode_scene == MODE_EQUIP_EDIT) {
					tenmetu(90, (110 + 20) + 20 * (whatedit1), 300 - 10,
						(110 + 20) + 20 * (1 + whatedit1));
				}
				if (mode_scene == MODE_EQUIP_EDIT2) {
					tenmetuStop(90, (110 + 20) + 20 * (whatedit1), 300 - 10,
						(110 + 20) + 20 * (1 + whatedit1));
				}


				// ����
				int soubiYbase = 110; int soubiYper = 20;

				lstrcpy(mojibuf, heros_def_list[partyNarabijyun[whomTargetID1]].heros_name);

				DrawFormatString(15, soubiYbase + soubiYper * 0, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				int stypeOffset = soubiOffset - 1; //10;
				for (int temp = 1; temp <= 7; temp = temp + 1) {

					int afterOffTemp = stypeOffset + temp;

					if (temp == 1) {
						lstrcpy(mojibuf1, TEXT("����"));
						lstrcpy(mojibuf2,

							soubihin[
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
							].Stype[afterOffTemp].def_name);

					}

					if (temp == 2) {
						lstrcpy(mojibuf1, TEXT("��"));
						lstrcpy(mojibuf2,

							soubihin[
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
							].Stype[afterOffTemp].def_name);
					}

					if (temp == 3) {
						lstrcpy(mojibuf1, TEXT("��"));
						lstrcpy(mojibuf2,
							soubihin[
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
							].Stype[afterOffTemp].def_name);

					}

					if (temp == 4) {
						lstrcpy(mojibuf1, TEXT("�g��"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					if (temp == 5) {
						lstrcpy(mojibuf1, TEXT("�r"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					if (temp == 6) {
						lstrcpy(mojibuf1, TEXT("�����i1"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					if (temp == 7) {
						lstrcpy(mojibuf1, TEXT("�����i2"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // ������`�悷��
					DrawFormatString(90, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // ������`�悷��

				}

				int temp = 8;

				lstrcpy(mojibuf1, TEXT("�U����"));
				DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // ������`�悷��

				_stprintf_s(mojibuf2, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[kougekiPara]);
				DrawFormatString(90 + 50, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // ������`�悷��


				temp = 9;
				lstrcpy(mojibuf1, TEXT("�����"));
				DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // ������`�悷��

				_stprintf_s(mojibuf2, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[syubiPara]);
				DrawFormatString(90 + 50, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // ������`�悷��


				// ���Ԃ�E�B���h�E�w�i�̐�
				window1Draw(10, 350, 500, 400);

				lstrcpy(mojibuf, TEXT("�ύX������������I��ł��������B"));
				DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				if (mode_scene == MODE_EQUIP_EDIT) {
					int locType;

					locType = soubiOffset + whatedit1;
					/*
					// ���L�͏�L�̃��t�@�N�^

					if (whatedit1 == 0) {
						locType = wepoType;
					}
					if (whatedit1 == 1) {
						locType = tateType;
					}
					if (whatedit1 == 2) {
						locType = kabutoType;
					}
					*/


					int tempSoubi = heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType];

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�����З� %d"), 0); // ����`�G���[��h�����߂̏�����

					if (locType == wepoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�����З� %d"), (soubihin[tempSoubi].Stype[locType]).equipPower[kougekiPara]);
					}
					if (locType == tateType || locType == kabutoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�����З� %d"), (soubihin[tempSoubi].Stype[locType]).equipPower[syubiPara]);
					}

					DrawFormatString(15 + 300 * 0, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}


				if (debugFlag == 1) {
					// �f�o�b�O���B�������Y���̃o�O�����B
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("whatedit2: %d"), whatedit2);
					DrawFormatString(15, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("iHw2: %d"), itemHairetu[whatedit2]);
					DrawFormatString(15 + 130, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("wHL: %d"), weapon_have_list[heros_def_list[partyNarabijyun[whomTargetID1]].heros_weapon1].have_def_id);
					DrawFormatString(15 + 130 + 100, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}


				if (nyuuryokuMatiZ > 0) {
					nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				}
				if (keyEnableZ == 0 && nyuuryokuMatiZ <= 0) {

					nyuuryokuMatiZ = 0;
					keyEnableZ = 1;

				}

				if (nyuuryokuMatiX > 0) {
					nyuuryokuMatiX = nyuuryokuMatiX - 1;

				}
				if (keyEnableX == 0 && nyuuryokuMatiX <= 0) {

					nyuuryokuMatiX = 0;
					keyEnableX = 1;

				}


				if (mode_scene == MODE_EQUIP_EDIT) {

					{
						if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1
							&& mode_scene == MODE_EQUIP_EDIT) {

							keyEnableReset();
							// MessageBox(NULL, TEXT("���܃R�R1"), TEXT("���b�Z�[�W"), MB_OK);

							key_remain = 0;
							whomTargetID1 = whomCHARA - 1;

							whatedit2 = 0;

							mode_scene = MODE_EQUIP_EDIT2;


							mode2_scene = MODE2_EQUIP_UnDef; // ����`�Ή��̂��߁A�Ƃ肠��������ɏ�����
							mode3_scene = 0;


							mode3_scene = whatedit1 + 11; // �����i�f�[�^�x�[�X��11�Ԃ���
							whatedit2 = heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubiKasol[mode3_scene];
						}

						CheckXetcFunc();
						if (CheckXetc && mode_scene == MODE_EQUIP_EDIT) {

							filterFlag = 0;
							mode_scene = MODE_EQUIP_MAIN;
							keyEnableReset();
						}

						CheckUPetcFunc();
						if (CheckUPetc) {

							// MessageBox(NULL, TEXT("�オ������܂����B"),
						// TEXT("�L�[�e�X�g"), MB_OK);
							whatedit1 = whatedit1 - 1;

							if (whatedit1 >= 5) {
								whatedit1 = 5;
							}
							else if (whatedit1 < 01) {
								whatedit1 = 0;
							}

							keyEnableReset();
						}


						CheckDOWNetcFunc();
						if (CheckDOWNetc) {
							// MessageBox(NULL, TEXT("����������܂����B"),
							// TEXT("�L�[�e�X�g"), MB_OK);
							whatedit1 = whatedit1 + 1;

							if (whatedit1 >= 5) {
								whatedit1 = 5;
							}
							else if (whatedit1 < 0) {
								whatedit1 = 0;
							}

							keyEnableReset();
						}

					}

				}


				int sentakuKougekiR = 0; //(soubihin[itemHairetu[whatedit2]].Stype[wepoType]).equipPower[kougekiPara];

				if (mode_scene == MODE_EQUIP_EDIT2) {

					if (CheckHitKey(KEY_INPUT_X) == 1) {

						filterFlag = 0;

						heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubiKasol[mode3_scene] = whatedit2;


						mode_scene = MODE_EQUIP_EDIT;
						keyEnableReset();
					}

					int souWInXsta = 400;
					int souWInXend = 580;

					// �����p�A�C�e���̃��X�g�\��
					// �w�i�̐�

					window1Draw(souWInXsta, 100, souWInXend, 300);

					tenmetu(souWInXsta + 20, (110 + 20) + 20 * (whatedit2), souWInXend - 30,
						(110 + 20) + 20 * (1 + whatedit2));

					weapon_have_list[0].have_kosuu = 0;


					// �ڐA��
					int itemskip = 0;
					goukeiItem = 0;

					int itemIDcount = 0;
					int column = 1; // �����R�}���h�̕���h��X�g��1�s�Ȃ̂�

					int xcommon;
					int ycommon;


					int locType;
					locType = mode3_scene;

					{

						// idTemp �͑����i��ނɑΉ�. 0 ������, 1���^�e 
						for (idTemp = 0; idTemp <= 2; idTemp = idTemp + 1)
						{
							itemHairetu[idTemp] = 0; // ����Ȃ��ƁA�����i���������Ƃ��c�[���c��B[]����idTemp�ł��邱�Ƃɒ���
						}

						for (idTemp = 0; idTemp <= 2; idTemp = idTemp + 1)
						{

							if ((soubiSyoji[idTemp].Stype[locType]).have_kosuu != 0) {

								xcommon = souWInXsta + 300 * floor((idTemp - itemskip) % column);
								ycommon = 130 + 20 * floor((idTemp - itemskip) / column);

								// �A�C�e�����̕\��
								lstrcpy(mojibuf, (soubihin[idTemp].Stype[locType]).def_name);
								DrawFormatString(xcommon, ycommon, GetColor(255, 255, 255), mojibuf); // ������`�悷��

								// ���̕\��
								_stprintf_s(mojibuf, MAX_LENGTH, TEXT("x %d"), (soubiSyoji[idTemp].Stype[locType]).have_kosuu);
								DrawFormatString(xcommon + 130, ycommon, GetColor(255, 255, 255), mojibuf); // ������`�悷��


								goukeiItem = goukeiItem + 1;

								itemHairetu[itemIDcount] = idTemp; // ����̓{�^�����쑤�Ŏg��
								itemIDcount = itemIDcount + 1; // ����͏�R�[�h�Ŏg��

							}

							if ((soubiSyoji[idTemp].Stype[locType]).have_kosuu == 0) {
								itemskip = itemskip + 1;
								itemHairetu[itemIDcount] = 0; // ����Ȃ��ƁA�������ʂ�ς����Ƃ��c�[���c��B
							}
						}

						CheckUPetcFunc();
						if (CheckUPetc) {

							// MessageBox(NULL, TEXT("�オ������܂����B"),
						// TEXT("�L�[�e�X�g"), MB_OK);
							whatedit2 = whatedit2 - 1;

							if (whatedit2 >= 5) {
								whatedit2 = 5;
							}
							else if (whatedit2 < 0 + 1) {
								whatedit2 = 0;
							}

							keyEnableReset();
						}


						CheckDOWNetcFunc();
						if (CheckDOWNetc) {

							whatedit2 = whatedit2 + 1;

							if (whatedit2 >= 5) {
								whatedit2 = 5;
							}
							else if (whatedit2 < 0) {
								whatedit2 = 0;
							}

							keyEnableReset();
						}

						CheckZetcFunc();
						if (CheckZetc && mode_scene == MODE_EQUIP_EDIT2) {

							keyEnableReset();

							key_remain = 0;


							int temp;

							int hensu = heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType];


							if (locType == wepoType) {
								// �U���͂̍X�V
								heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[kougekiPara] =
									(soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[kougekiPara];

							}
							sentakuKougekiR = (soubihin[itemHairetu[whatedit2]].Stype[wepoType]).equipPower[kougekiPara]; // �\���ł��g���̂ōė��p

							(soubiSyoji[hensu].Stype[locType]).have_kosuu =
								(soubiSyoji[hensu].Stype[locType]).have_kosuu + 1; // �������Ă����킪1������悤��


							if (whatedit2 < goukeiItem) {

								//itemHairetu
								(soubiSyoji[itemHairetu[whatedit2]].Stype[locType]).have_kosuu
									= (soubiSyoji[itemHairetu[whatedit2]].Stype[locType]).have_kosuu - 1; // 


							}
							if (whatedit2 >= goukeiItem) {
								// �����I�����ĂȂ���ԂȂ̂ŁA��������Ȃ�
								//weapon_have_list[whatedit2 + 1].have_kosuu = weapon_have_list[whatedit2 + 1].have_kosuu - 1;  // �J�[�\���I�𒆂��������킪1����
							}


							if (whatedit2 < goukeiItem) {
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType] =

									soubihin[itemHairetu[whatedit2]].Stype[locType].def_id; // 

							}
							if (whatedit2 >= goukeiItem) {
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType] =
									soubihin[0].Stype[locType].def_id; // �����̍X�V��������
							}



							/////////////

							if (locType == tateType || locType == kabutoType) {

								// �h��̍X�V // ���łɂ��Ă���

								//(soubihin[heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType]].Stype[locType]).equipPower[syubiPara] =
								//	(soubihin[heros_def_list[itemHairetu[whatedit2]].heroSoubi[locType]].Stype[locType]).equipPower[syubiPara]
								//	;


								// �h��͂̍X�V
								heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[syubiPara] = // ���݂̒l

									(soubihin[(heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[tateType])].Stype[tateType]).equipPower[syubiPara]
									+ (soubihin[(heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[kabutoType])].Stype[kabutoType]).equipPower[syubiPara]
									;

							}

							//////////

							(soubiSyoji[0].Stype[locType]).have_kosuu = 0;

						}

					} // �E�F�|��

				}

				if (mode_scene == MODE_EQUIP_EDIT2) {

					int locType;
					locType = mode3_scene;

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT(""), 0); // ����`�G���[����h�����߂̏�����

					if (locType == wepoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�����З� %d"), (soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[kougekiPara]);
					}

					if (locType == tateType || locType == kabutoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�����З� %d"), (soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[syubiPara]);
					}

					DrawFormatString(15 + 300, 350 + 10, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}
			} // end of MODE_EQUIP_ ��`��


			if (mode_scene == skillMode) {

				CheckXetcFunc();
				if (CheckXetc) {
					mode_scene = MODE_MENU;

					endX2();

					DrawFormatString(250, 250 + 50 * 2, GetColor(255, 255, 255), "���Z����߂�"); // ������`�悷��

				}
			}

			key_remain = 1;

			ScreenFlip(); //����ʂ�\��ʂɔ��f
		}

	}


	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 


}

