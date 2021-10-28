#include "DxLib.h"


#include <stdio.h> // �Z�[�u�p
#pragma warning(disable:4996) // fopen


#include <math.h>  // �؂�グ�v�Z�Ŏg�p

int waitheal = 0; // �񕜂̕\�����̒���
int damepyon = 0; // �퓬���Ƀ_���[�W���s�����Ɠ������A��
int tekidame = 0; // �G�̃_���[�W�󂯂Ă�Ԃ����I��
int mikatadame = 0; // mikata�̃_���[�W�󂯂Ă�Ԃ����I��

int senkaFlag = 0;

int wind1R = 50;
int wind1G = 50;
int wind1B = 150;

int window1color = GetColor(wind1R, wind1G, wind1B); // �E�B���h�E�̂ق��A�J�[�\���̃x�[�X�F�ł��g���\��������̂ŕϐ����B
void window1Draw(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		window1color, 1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255, 255, 255), 0);

}

int darkwindow1color = GetColor(wind1R /2, wind1G /2, wind1B /2);
void darkwindow1Draw(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		darkwindow1color, 1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255/2, 255/2, 255/2), 0);

}

int debugFlag = 0;

int casolu1R = 250; // l �� 1 �̋�ʂ̂��� u �ǉ�
int casolu1G = 150;
int casolu1B = 150;

int KasolColor = GetColor(casolu1R, casolu1G, casolu1B);
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


	int whiteMax = 180;

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

	int whiteMax = 180;

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


int monPosiX = 4; int monPosiY = 3; // �}�b�v��Ń����X�^�[�̂�����W


int map1table[10][10] = {
	{ 1,1,1,1,1,1,1,1,1,1 }, //0 y
{ 1,0,0,0,0,0,0,0,0,1 }, //1
{ 1,0,0,0,0,0,0,0,0,1 }, //2
{ 1,0,0,0,0,0,0,0,0,1 }, //3
{ 1,0,0,0,0,0,0,0,0,1 }, //4
{ 1,0,0,0,0,0,0,0,0,1 }, //5
{ 1,1,1,1,1,1,0,0,1,1 }  //6
};


int x_mapDraw = 0;
int y_mapDraw = 0;

int hero1HPnow = 20;
int hero1HPmax = 50;


int hero2HPnow = 14;
int hero2HPmax = 30;


int toubouTyokugo = 0;


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


int waitTime1 = 60;
int waitTime2 = 30;


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

	MODE_BATTLE_COMMAND, MODE_BATTLE_NOW, MODE_BATTLE_WIN, BATTLE_Agility_proc,

	MODE_Guild_Main, MODE_Guild_Responce, MODE_Guild_Remove,

	itemModeMain, itemModeTarget, skillMode,
};
enum mode mode_scene = MODE_MAP;


enum mode2 {
	MODE2_EQUIP_UnDef, // ����`�Ή�
	MODE2_EQUIP_HAND1,
	MODE2_EQUIP_SHIELD,
	MODE2_EQUIP_HELM,
	MODE2_EQUIP_ARMOR
};
enum mode2 mode2_scene = MODE2_EQUIP_HAND1;

int mode3_scene = 0 ;


int yakusouKosuu = 5;
int dokukesiKosuu = 3;
int soesiKosuu = 4;


int NaraSele1 = 0;

int NaraSele2 = 0;


int uketKyara = 1; // �퓬���ŁA���l�ڂ��_���[�W�󂯂Ă邩�B�u1�v��1�l�ځB

int pageSyori = 0;


// �A�C�e����ޔԍ�
int siyouType = 10; // 0�`9�Ԃ̓V�X�e�������p�Ɋm��

int soubiOffset = 11; // wepoType�Ɠ��ԍ������A�g������ǐ����l���A�ʕϐ���p��

int wepoType = soubiOffset ; // 11
int tateType = soubiOffset + 1; // 12;
int kabutoType = soubiOffset + 2; // 13;

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

int whatedit = 0; // �����R�}���h�ȂǁA�ҏW�����邢�낢��ȍ�Ɨp
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

int whomTargetID1party = 0;
int whomTargetID1hikae = 0;


int filterFlag = 0;

int FontYoffset = 30;

int idTemp = 0;
int battleID = 0;
int globalTempA = 0;
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


static int encount_monters_id = 2;


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


static TCHAR filename_temp[100]; // �t�@�C���ǂݏ����Ŏg���ꎞ�I�ȃt�@�C����


static int mode2_mode_scene = 0;

static int selecting_OP = 1;

static int cursol_stop;
static int your_money = 0;



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

	if (selecting_item < 1) {
		selecting_item = 1;
	}

	if (selecting_item > goukeiItem) {
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


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[partyNarabijyun[j]].heros_name);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		lstrcpy(mojibuf, TEXT("HP"));
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_hp);
		DrawFormatString(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


		int revwait = 120 - waitheal;

		if (healflag == 1 && healkioku == j) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 +20, StatsHPbaseY -20 + offsetY * j  +20 - 2 * revwait, GetColor(10, 255, 10), mojibuf); // ������`�悷��

		}

		if (healflag == 2 && healkioku == j) {

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 +20, StatsHPbaseY - 20 + offsetY * j - (60) / 6, GetColor(10, 255, 10), mojibuf); // ������`�悷��

		}


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[partyNarabijyun[j]].heros_hp_max);
		DrawFormatString(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��


		if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�퓬�s�\"));
			DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��

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

	monster_hp = monster_def_list[encount_monters_id - 1].mon_hp_max;

	_stprintf_s(monster_name, MAX_LENGTH, TEXT("%s"), monster_def_list[encount_monters_id - 1].monster_name);
	tekiTairetuAgility[0] = monster_def_list[encount_monters_id - 1].mon_agility;

	encount_mons_alive = 1;
	selecting_battle_mainmenu = 1;
	enemyAlldeadFlag = 0;

	mode_scene = MODE_BATTLE_COMMAND;

}


// �����X�^�[�Ƃ̑�������
void check_encount_enemy(HWND hWnd) {

	if (where_map == 2) {
		for (int i = 0; i <= 1; i = i + 1)
		{
			if (enemy_alive[i] == 1) {
				if (chara_x == positionX_enemy[i] && chara_y == positionY_enemy[i]) {

					encount_monters_id = i + 1;	// �����ɁA�N�Ƒ������������L�q

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


void check_encount_town() {

	if (where_map == 1 && chara_x == town_X && chara_y == town_Y) {

		popFlagTown = 1;
		lstrcpy(popMsg, TEXT("�p�[�e�B�̕Ґ����ł��܂��B"));

		mode_scene = MODE_TOWN;
		// pre_guild(hWnd); // �̂��̂��̃M���h�����̂��ߎc��

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

	int pnCommon = partyNarabijyun[actionOrder[globalTempA]];

	if (heros_def_list[pnCommon].heros_HP0_flag == 0) {
		// ��l�������̍U��

		/* �����̎� */			
		// wWinMain �Œ�`�ς�
			
		/* �T�C�R�� */
		damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_para[kougekiPara];

		// �G�Ƀ_���[�W
		monster_hp = monster_hp - damage_HeroAttack;

		// �����X�^�[�̎��S�̏���
		if (monster_hp < 1) {
			monster_hp = 0;

			enemy_alive[(encount_monters_id)-1] = 0; // �t�B�[���h��̓G�̏���

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

	int pnCommon = partyNarabijyun[actionOrder[globalTempA]];

	// �_���[�W�v�Z��
	/* �T�C�R�� */
	damage_EnemyAttack = rand() % (6 / 2) + 10 + 2 * monster_def_list[encount_monters_id - 1].mon_attackPower
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

	darkFlag = 1;
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
		ViewFlag[1] = 0;  // ViewFlagItem = 0;
		ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
		ViewFlag[3] = 0;  // ViewFlagShield = 0;
		ViewFlag[4] = 0;  // ViewFlagHelm = 0;

		// �\���t���O�ݒ�
		if (mode_scene == MODE_ITEM_MENU || (selecting_mainmenu == 1 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 1;  // ViewFlagItem = 1;
			ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
			ViewFlag[3] = 0;  // ViewFlagShield = 0;
			ViewFlag[4] = 0;  // ViewFlagHelm = 0;
		}

		if (mode_scene == MODE_ITEMweapon_MENU || (selecting_mainmenu == 2 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;  // ViewFlagItem = 0;
			ViewFlag[2] = 1;  // ViewFlagWeapon = 1;
			ViewFlag[3] = 1;  // ViewFlagShield = 1;
			ViewFlag[4] = 1;  // ViewFlagHelm = 1;
		}

		if ((selecting_mainmenu == 3 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;   //ViewFlagItem = 0;
			ViewFlag[2] = 0;   //ViewFlagWeapon = 0;
			ViewFlag[3] = 0;   //ViewFlagShield = 0;
			ViewFlag[4] = 0;   //ViewFlagHelm = 0;
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
	for (int tempVal1 = 2; tempVal1 <= 4; tempVal1 = tempVal1 +1) {

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
			if (itemTypeHairetu[temp2] == wepoType
				|| itemTypeHairetu[temp2] == tateType
				|| itemTypeHairetu[temp2] == kabutoType
				) {

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

				lstrcpy(mojibuf, (soubihin[itemHairetu[temp2]].Stype[locType]).def_name);

			}

			DrawFormatString(xcommon, ycommon, GetColor(255, 255, 255), mojibuf);

			// �����̔w�i�N���A�p
			lstrcpy(mojibuf, TEXT("   "));
			DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf);


			if (itemTypeHairetu[temp2] == siyouType) {
				// ����̌��\��. �\���͌㏈����DrawFormat �ňꊇ
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), item_have_list[itemHairetu[temp2]].have_kosuu);
			}

			int locType = itemTypeHairetu[temp2];
			if (itemTypeHairetu[temp2] == wepoType || itemTypeHairetu[temp2] == tateType
				|| itemTypeHairetu[temp2] == kabutoType
				) {
				// �����i�̌��\��. �\���͌㏈����DrawFormat �ňꊇ
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[itemHairetu[temp2]].Stype[locType]).have_kosuu);
			}

			// ��L��������ۂɕ\������
			DrawFormatString(xcommon + 130, ycommon, GetColor(255, 255, 255), mojibuf);

		}
	} // ����R�}���h�̓���\���═��\���Ȃ�

	itemIDcount = 0;
} // itemlist



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


	int koboHandle = LoadGraph("GameData\\monster_graphic\\kobo.png");
	int monchipDownHandle = LoadGraph("GameData\\charachip\\enemy_dot.bmp");
	int blackchipHandle = LoadGraph("GameData\\charachip\\blackchip.bmp");


	int blackbackHandle = LoadGraph("GameData\\picture\\blackBigBack.bmp");


	int charachipUpHandle = LoadGraph("GameData\\charachip\\hero_dot_up.bmp");
	int charachipDownHandle = LoadGraph("GameData\\charachip\\hero_dot_down.bmp");
	int charachipLeftHandle = LoadGraph("GameData\\charachip\\hero_dot_left.bmp");
	int charachipRightHandle = LoadGraph("GameData\\charachip\\hero_dot_right.bmp");


	// �A�C�e���̏��
	int tourokuItem = 3;
	for (int temp = 0; temp <= tourokuItem; temp++) {

		item_def_list[temp].def_id = temp;
		item_def_list[temp].item_type = siyouType;

		if (temp == 0) {
			//�򑐂̒�`
			lstrcpy(item_def_list[temp].def_name, TEXT("--------"));
		}

		if (temp == 1) {
			//�򑐂̒�`
			lstrcpy(item_def_list[temp].def_name, TEXT("��"));
		}

		if (temp == 2) {
			lstrcpy(item_def_list[temp].def_name, TEXT("�ŏ�����"));
		}

		if (temp == 3) {
			lstrcpy(item_def_list[temp].def_name, TEXT("�s�����̔�")); // �����̗��R�͎����̐ߖ�			
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


	// �����X�^�[�̒�`	
	for (int temp = 0; temp <= 1; temp++) {

		if (temp == 0) {
			lstrcpy(monster_def_list[temp].monster_name, TEXT("�X���C��"));
			monster_def_list[temp].mon_hp_max = 12;
			monster_def_list[temp].mon_agility = 13;
			monster_def_list[temp].monster_id = 1;
			monster_def_list[temp].mon_gold = 1;
			monster_def_list[temp].mon_exp = 2;
			monster_def_list[temp].mon_attackPower = 0;
		}

		if (temp == 1) {
			lstrcpy(monster_def_list[temp].monster_name, TEXT("�R�{���g"));
			monster_def_list[temp].mon_hp_max = 90;
			monster_def_list[temp].mon_agility = 76;
			monster_def_list[temp].monster_id = 2;
			monster_def_list[temp].mon_gold = 10;
			monster_def_list[temp].mon_exp = 5;
			monster_def_list[temp].mon_attackPower = 1;
		}

	}


	// �L�����N�^�[�̒�`
	for (int temp = 0; temp <= makeNakamaNinzu + 1; temp++) {

		if (temp == 0) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("�G���X"));
			heros_def_list[temp].heros_hp = 132; // 20;
			heros_def_list[temp].heros_hp_max = 185;
			heros_def_list[temp].heros_agility = 56;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;


			heros_def_list[temp].heroSoubi[wepoType] = 1;
			heros_def_list[temp].heroSoubiKasol[wepoType] = 0;

			heros_def_list[temp].heroSoubi[tateType] = 0;
			heros_def_list[temp].heroSoubi[tateType] = 1;

			heros_def_list[temp].heros_para[kougekiPara] = (soubihin[heros_def_list[temp].heroSoubi[wepoType]].Stype[wepoType]).equipPower[kougekiPara];

			heros_def_list[temp].heros_para[syubiPara] = (soubihin[heros_def_list[temp].heroSoubi[tateType]].Stype[tateType]).equipPower[syubiPara]
				+ (soubihin[heros_def_list[temp].heroSoubi[kabutoType]].Stype[kabutoType]).equipPower[syubiPara]
				;
			
		}

		if (temp == 1) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("�s�G�|��"));
			heros_def_list[temp].heros_hp = 108; //  18;
			heros_def_list[temp].heros_hp_max = 150;
			heros_def_list[temp].heros_agility = 100;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;



			heros_def_list[temp].heroSoubi[wepoType] = 2;
			heros_def_list[temp].heroSoubi[tateType] = 0;


			heros_def_list[temp].heros_subiRyoku = (soubihin[heros_def_list[temp].heroSoubi[tateType]].Stype[tateType]).equipPower[syubiPara];

			heros_def_list[temp].heros_para[kougekiPara] = (soubihin[heros_def_list[temp].heroSoubi[wepoType]].Stype[wepoType]).equipPower[kougekiPara];
			heros_def_list[temp].heros_para[syubiPara] = (soubihin[heros_def_list[temp].heroSoubi[tateType]].Stype[tateType]).equipPower[syubiPara];



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


		if (keyEnableUp == 0 && nyuuryokuMatiUp > 0) {
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

		int mapChipWidthX = 30;
		int mapChipWidthY = 30;

		for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)
		{
			for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw)
			{
				if (map1table[y_mapDraw][x_mapDraw] == 0) {
					DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * y_mapDraw, mapchip1Handle, false);
				}
				if (map1table[y_mapDraw][x_mapDraw] == 1) {
					DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * y_mapDraw, mapchip2Handle, false);
				}
			}

		}


		DrawGraph(mapChipWidthX * monPosiX, mapChipWidthY * monPosiY, monchipDownHandle, false);



		// �L�����`�b�v�`��
		{
			int charaChipWidthX = 30; // ����if�̊O�ł��g���̂Ńu���b�N�O�Œ�`�B
			int charaChipWidthY = 30;

			if (xPosi == monPosiX && yPosi == monPosiY) {

				// �����X�^�[�摜 �N���[���p
				DrawGraph(charaChipWidthX * monPosiX, charaChipWidthY * monPosiY, blackchipHandle, false);

			}



			// �ʂ̌����̉摜�ŏ㏑��

			double baiX = waitTime1 / charaChipWidthX;
			double baiY = waitTime1 / charaChipWidthY;

			if (hero1_direction == rightward) {

				tempHandle = charachipRightHandle;
				DrawGraph(charaChipWidthX * xPosi + 0 + (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY * yPosi, tempHandle, false);
			}

			if (hero1_direction == leftward) {
				tempHandle = charachipLeftHandle;
				DrawGraph(charaChipWidthX * xPosi + 0 - (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY * yPosi, tempHandle, false);

			}



			if (hero1_direction == downward) {
				tempHandle = charachipDownHandle;
				DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * yPosi + (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);

			}

			if (hero1_direction == upward) {
				tempHandle = charachipUpHandle;
				DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * yPosi - (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);
			}

		}


		if (mode_scene == MODE_MAP) {
			// �ړ��L�[�̃t���O����
			{
				int mapsizeX = 10; int mapsizeY = 7;
				
				{ // �ړ��̃��W���[��

					// �L�������E�Ɉړ�
					if (xPosi < mapsizeX && yPosi < mapsizeY + 1 ) { // y���� ��+1 ���Ă�̂̓f�o�b�O�p
						// �ړ���\��n�̓���ۂ̔���
						if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1 && moving == 0) {
							if (map1table[yPosi][xPosi + 1] == 1) { destMovable = 0; }
							if (map1table[yPosi][xPosi + 1] == 0) { destMovable = 1; }

							// ����\�Ȃ�t���O�ݒ�
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = rightward;
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

							nyuuryokuMatiLR = waitTime1;
							nyuuryokuMatiLeft = waitTime1;
							nyuuryokuMatiRight = waitTime1;


							xPosi++;     // �E��1�}�X�����ړ�
							moving = 0;
						}
					} // �E�ړ�

					// ���Ɉړ�
					if (xPosi < mapsizeX + 1 && yPosi < mapsizeY + 1 ) {      // y���� ��+1 ���Ă�̂̓f�o�b�O�p
						// �ړ���\��n�̓���ۂ̔���
						if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1 && moving == 0) {
							if (map1table[yPosi][xPosi - 1] == 1) { destMovable = 0; }
							if (map1table[yPosi][xPosi - 1] == 0) { destMovable = 1; }

							// ����\�Ȃ�t���O�ݒ�
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = leftward;
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
						}
					}// ���Ɉړ�

					// ���Ɉړ�
					if (xPosi < mapsizeX  && yPosi < mapsizeY ) {
						// �ړ���\��n�̓���ۂ̔���
						if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1 && moving == 0) {
							if (map1table[yPosi + 1][xPosi] == 1) { destMovable = 0; }
							if (map1table[yPosi + 1][xPosi] == 0) { destMovable = 1; }

							// ����\�Ȃ�t���O�ݒ�
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = downward;
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
						if (hero1_direction == downward && nyuuryokuMatiUD <= 0) {
							keyEnableDown = 1;

							nyuuryokuMatiUD = waitTime1;
							nyuuryokuMatiUp = waitTime1;
							nyuuryokuMatiDown = waitTime1;

							yPosi++;     // ����1�}�X�����ړ�
							moving = 0;
						}
					}// ���Ɉړ�


					// ��Ɉړ�
					if (xPosi < mapsizeX  && yPosi < mapsizeY + 1) {
						// �ړ���\��n�̓���ۂ̔���
						if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && moving == 0) {
							if (map1table[yPosi - 1][xPosi] == 1) { destMovable = 0; }
							if (map1table[yPosi - 1][xPosi] == 0) { destMovable = 1; }

							// ����\�Ȃ�t���O�ݒ�
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = upward;
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
						}
					}// ��Ɉړ�
				}// �ړ�

				// ���S�����̃t���O�ݒ���ۂ�
				if (destMovable == 1 && moving == 1 && toubouTyokugo > 0) {
					toubouTyokugo = toubouTyokugo - 1;
					destMovable = 0;
				}
				if (toubouTyokugo <= 0) {
					toubouSeikou = 0;
					toubouTyokugo = 0;
				}

				// �����X�^�[�����̃G���J�E���g����
				{
					int monMesX = 400; int monMesY = 350; // ���b�Z�[�W���̕\���ʒu


					if (xPosi == monPosiX && yPosi == monPosiY && toubouTyokugo == 0) {
						battle_start();
						mode_scene = MODE_BATTLE_COMMAND;

						DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
							GetColor(0, 0, 0), 1);
						DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�����X�^�[�����ꂽ������"); // ������`�悷��

						// �����X�^�[�摜 // �f�o�b�O�p
						DrawGraph(300, 95, koboHandle, true);
					}

					if (!(xPosi == monPosiX && yPosi == monPosiY)) {
						DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
							GetColor(0, 0, 0), 1);
						DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�e�X�g�p���b�Z�[�W"); // ������`�悷��

					}

				} // �����X�^�[��������
			}

			// if �c��ҋ@���[���ŁA�����X�{�^���������ꂽ��Athen ���j���[��ʂɑJ��
			if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
				keyEnableX = 0;
				mode_scene = MODE_MENU;
				nyuuryokuMatiX = waitTime1;
			}

			window1Draw(100, 250, 100 + 150, 250 + 40 + 100);

			DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��

		} // map ���[�h�̏I���


		if (mode_scene == MODE_BATTLE_COMMAND || mode_scene == MODE_BATTLE_NOW || mode_scene == MODE_BATTLE_WIN) {

			int monMesX = 400; int monMesY = 350; // ���b�Z�[�W���̕\���ʒu
			DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
				GetColor(0, 0, 0), 1);
			DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�����X�^�[�����ꂽ"); // ������`�悷��

			// �����X�^�[�摜 
			if (mode_scene == MODE_BATTLE_COMMAND || mode_scene == MODE_BATTLE_NOW) {

				DrawGraph(300, 95, koboHandle, true);
			}


			if (mode_scene == MODE_BATTLE_COMMAND) {
				int tem1X = 100; int Xwidth = 100;
				int tem1Y = 240;

				int yohakuY = 10;
				window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
					tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

				// �J�[�\��
				tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
					tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);

				DrawFormatString(tem1X + 20, tem1Y + 10, GetColor(255, 255, 255), "�키"); // ������`�悷��
				DrawFormatString(tem1X + 20, tem1Y + 10 + 40, GetColor(255, 255, 255), "������"); // ������`�悷��
			}


			// �G�֌W�̃p�����|�^�\��
			int monX = 450;
			int monY = 150;

			tekiTairetuAgility[0] = monster_def_list[encount_monters_id - 1].mon_agility;


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


			if (mode_scene == MODE_BATTLE_NOW) {

				int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 �́uwindowTempA�v

				int pnCommon = partyNarabijyun[actionOrder[globalTempA]];

				if (heros_def_list[pnCommon].heros_HP0_flag == 0) {
					if (actionOrder[globalTempA] <= partyNinzuDone - 1) {

						_stprintf_s(mojibuf, TEXT("%s �̍U���I"), heros_def_list[pnCommon].heros_name);
						DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

						// �f�o�b�O��
						if (debugFlag == 1) {
							_stprintf_s(mojibuf, TEXT("gte %d"), globalTempA);
							_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[globalTempA]);
							_stprintf_s(mojibuf, TEXT("pag���� %d"), partyNarabijyun[actionOrder[globalTempA]]);							
						} // �����܂Ńf�o��

					}
				}

				if (heros_def_list[partyNarabijyun[actionOrder[globalTempA]]].heros_HP0_flag == 1) {
					if (actionOrder[globalTempA] <= partyNinzuDone - 1) {
						_stprintf_s(mojibuf, TEXT("%s �͐퓬�s�\�œ����Ȃ�"), heros_def_list[partyNarabijyun[actionOrder[globalTempA]]].heros_name);
						DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
				}

				if (actionOrder[globalTempA] >= partyNinzuDone) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�G�̍U���I "));
					DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				}



				// DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "�키�e�X�g"); // ������`�悷��

				if (PorEflag[globalTempA] == tekiPE) {
					if (encount_mons_alive == 1) {

						// enemy atack �Ł@tekidame =0 �ɂ���Ă�
						if (damepyon < 10 && tekidame == 0) {
							damepyon = damepyon + 1;
						}

						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d �_���[�W"), damage_EnemyAttack);
						DrawFormatString(30, 350 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
				}

				if (PorEflag[globalTempA] == mikataPE) {
					if (encount_mons_alive == 1 || encount_mons_alive == 0) {

						// hero atack �Ł@tekidame =1 �ɂ���Ă�
						if (damepyon < 10 && tekidame == 1) {
							damepyon = damepyon + 1;
						}

						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d �_���[�W"), damage_HeroAttack);
						DrawFormatString(monX + 10, monY - 30 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // ������`�悷��

					}
				}

			}// now



			// �\���L�[���͎�
			if (keyHaijyo == 0) {
				// �J�[�\������Ɉړ�

				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
						keyEnableUp = 0;
						nyuuryokuMatiUp = waitTime1;
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
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
						keyEnableDown = 0;
						nyuuryokuMatiDown = waitTime1;
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


			// �^�[���J�n
			if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == 1 && keyHaijyo == 0 				
				&& mode_scene != MODE_BATTLE_NOW       // ���ꂪ�����ƘA�łŃ^�[���ĊJ���Ă��܂�
				&& mode_scene != MODE_BATTLE_WIN ) { // ���ꂪ�����ƘA�łŃ^�[���ĊJ���Ă��܂�

				// MessageBox(NULL, TEXT("test�B"), TEXT("�ꏊ�e�X�g"), MB_OK);

				TimeKasolCount = 0;

				keyHaijyo = 1;
				battlewait = 100;

				dameKei = 0;

				damage_EnemyAttack = 0;
				damage_HeroAttack = 0;

				mode_scene = MODE_BATTLE_NOW;		

			}

			battlewait = battlewait - 1;


			


			if (mode_scene == MODE_BATTLE_WIN) {
			
				DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "�|����"); // ������`�悷��

				int senkaX = 250; int senkaY = 150;
				window1Draw(senkaX, senkaY, senkaX + 150, senkaY + 120 );

				int offsetY2 = FontYoffset;
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Exp: %d"), monster_def_list[encount_monters_id - 1].mon_exp);
				DrawFormatString(senkaX + 10, senkaY + offsetY2 * 1, GetColor(255, 255, 255), mojibuf); // ������`�悷��

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Gold: %d"), monster_def_list[encount_monters_id - 1].mon_gold);
				DrawFormatString(senkaX + 10, senkaY + offsetY2 * 2, GetColor(255, 255, 255), mojibuf); // ������`�悷��


				keyHaijyo = 1; // �퓬�R�}���h�����s����Ȃ��悤�A�܂��r����

				toubouTyokugo = 5;


				if (battlewait <= 0 && senkaFlag == 0) {

					globalTempA = 0; // �^�[���I������

					// MessageBox(NULL, TEXT("�G�|�����B"), TEXT("�ꏊ�e�X�g"), MB_OK);

					// �J�l�ƌo���l�̍X�V
					your_money = your_money + monster_def_list[encount_monters_id - 1].mon_gold;

					for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {

						// �o�^�L�����������ꍇ��z�肵�āi���jSLG�Ȃǁj�A�S�L�����͑������Ȃ��B							
						// MessageBox(NULL, TEXT("�G�|�����B"), TEXT("�ꏊ�e�X�g"), MB_OK);

						heros_def_list[partyNarabijyun[temp]].heros_exp = heros_def_list[partyNarabijyun[temp]].heros_exp + monster_def_list[encount_monters_id - 1].mon_exp;

					}					
					senkaFlag = 1;
				}


				if (CheckHitKey(KEY_INPUT_Z) == 1 && senkaFlag == 1) {
					globalTempA = 0; // �^�[���I��

					keyEnableReset();
					keyHaijyo = 0;
					mode_scene = MODE_MAP;// �e�X�g�p�ɓ|���������Ȃ̂�
				}
			} // win


			if (mode_scene == MODE_BATTLE_NOW && dameKei == 0) {

				if (PorEflag[globalTempA] == 1	) {

					if (encount_mons_alive == 1) {
						heroside_attack();
						dameKei = 1;
					}
				}

				if (PorEflag[globalTempA] == tekiPE) {
					if (encount_mons_alive == 1) {

						enemy_attack();
						dameKei = 1;
					}
				}
			}

			// ���s����(globalTempA )���Z�b�g
			if (battlewait <= 0 && mode_scene == MODE_BATTLE_NOW && dameKei == 1) {
				battlewait = 0;
				dameKei = 0;

				if (monster_hp <= 0) {			
					mode_scene = MODE_BATTLE_WIN;
					battlewait = 60.0 * 2.0;
				}
				if (monster_hp > 0) {

					if (globalTempA <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 && dameKei == 0) {

						// MessageBox(NULL, TEXT("aaa"), TEXT("�ꏊ�e�X�g"), MB_OK);

						globalTempA = globalTempA + 1;
						battlewait = 60.0 * 2.0;
					}



					// �^�[���I��					
					if (globalTempA >= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 + 1) {

						// MessageBox(NULL, TEXT("qwerty"), TEXT("�ꏊ�e�X�g"), MB_OK);
						damage_EnemyAttack = 0;
						damage_HeroAttack = 0;

						globalTempA = 0;

						damepyon = 0;
						mode_scene = MODE_BATTLE_COMMAND;											
					}
				}
				keyHaijyo = 0;
			} // battlewait ��0�̏��





			if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == 2 && keyHaijyo == 0) {

				keyHaijyo = 1;

				TimeKasolCount = 0;
				DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "������̂ɐ���"); // ������`�悷��
				toubouSeikou = 1;
				toubouTyokugo = 5;

			}

			if (toubouSeikou == 1) {
				DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "������̂ɐ���"); // ������`�悷��

			}

			if (toubouSeikou == 1 && TimeKasolCount == 60) {
				keyHaijyo = 0;
				mode_scene = MODE_MAP;

			}
		}


		if (mode_scene == MODE_MENU) {
			int HPX = 300; int HPY = 50;
			int shiftY = 80;
			// �E�B���h�E��

			window1Draw(HPX, HPY, HPX + 150, HPY + 100 *2);

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
					DrawFormatString(XXX + 20, YYY + 40 * j, GetColor(255 , 255 , 255), mojibuf); // ������`�悷��

				}


				// �\���L�[���͎�

				// �J�[�\������Ɉړ�
				{

					// �ړ��̏I������
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
						keyEnableUp = 0;
						nyuuryokuMatiUp = waitTime1;
						selecting_mainmenu--;     // ���1�}�X�����ړ�

					}


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
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
						keyEnableDown = 0;
						nyuuryokuMatiDown = waitTime1;
						selecting_mainmenu++;    // ����1�}�X�����ړ�
					}


					if (selecting_mainmenu < 1) {
						selecting_mainmenu = 1;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}

				}


				if (CheckHitKey(KEY_INPUT_Z) == 1) {

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

			darkwindow1Draw(darkWinX +XXX - damepyon, darkWinY, darkWinX + 110 + XXX - damepyon, darkWinY + 200);
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
				itemList(soubihin, soubiSyoji,0 );
		
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


			if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0 && keyEnableX == 1) {

				{
					key_remain = 0;
					damepyon = 0;

					mode_scene = MODE_MENU;
					keyEnableX = 0;
					nyuuryokuMatiX = waitTime1;
				}
				keyEnableUp = 0;

				keyEnableDown = 0;

				kasol2Target = 0;
				selecting_mainmenu = 1;
			}


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

				if (selecting_mainmenu >= 3) {
					selecting_mainmenu = 3;
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

				if (selecting_mainmenu >= 3) {
					selecting_mainmenu = 3;
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


		if (mode_scene == itemModeTarget) {

			int itemWindX = 450;
			int itemWindY = 50;


			// �f�o�b�O�p
			DrawFormatString(itemWindX, 250 + 150 - 20, GetColor(255, 255, 255), "kkkkkkk"); // ������`�悷��

			// �J�E���g����
			if (keyEnableZ == 2 && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;
				keyEnableZ = 3;
				// �f�o�b�O�p
				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // ������`�悷��
			}


			if (nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

			}

			if (nyuuryokuMatiZ <= 0) {
				nyuuryokuMatiZ = 0;

			}

			int HPX = 300; int HPY = 50;

			window1Draw(HPX, HPY, HPX + 150, HPY + 340 + 50);


			// �J�[�\��
			tenmetu(HPX, HPY + kasol3Target * 60, HPX + 130, HPY + 50 + kasol3Target * 60);

			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // ������`�悷��			
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // ������`�悷��

			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // ������`�悷��
			DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // ������`�悷��


			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

			}

			if (nyuuryokuMatiX <= 0) {
				nyuuryokuMatiX = 0;
				keyEnableX = 1;

			}

			// �\���L�[���͎�
			// �J�[�\������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 0 && moving == 0) {

					// ����\�Ȃ�t���O�ݒ�
	
					moving = 1;

					keyEnableUp = 1;
					waitKasol = 20;
					
				}

				// �J�E���g����
				if (keyEnableUp == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}

				// �ړ��̏I������
				if (keyEnableUp == 1 && waitKasol <= 0) {
					keyEnableUp = 0;
					waitKasol = waitTime1;
					kasol3Target--;      // ���1�}�X�����ړ�
					moving = 0;
				}

				if (kasol3Target < 0) {
					kasol3Target = 0;
				}

				if (kasol3Target >= 3) {
					kasol3Target = 3;
				}
			}


			// �J�[�\�������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 0 && moving == 0) {

					// ����\�Ȃ�t���O�ݒ�
	
					moving = 1;

					keyEnableDown = 1;
					waitKasol = 20;
		
				}
				// �J�E���g����
				if (keyEnableDown == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// �ړ��̏I������
				if (keyEnableDown == 1 && waitKasol <= 0) {
					keyEnableDown = 0;
					waitKasol = 20;
					kasol3Target++;   // ����1�}�X�����ړ�
					moving = 0;
				}


				if (kasol3Target < 0) {
					kasol3Target = 0;
				}

				if (kasol3Target >= 3) {
					kasol3Target = 3;
				}
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0) {
				keyEnableReset();

				// �R�s�y�p�ɂق��̃C�R�[�����c���Ƃ�
				// mode_scene = itemModeMain; // mode_scene == MODE_ITEM_TYPE
				mode_scene = MODE_ITEM_MENU; // mode_scene == MODE_ITEM_TYPE

				nyuuryokuMatiX = waitTime1;
			}

			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

				// ���s�����ƃJ�E���g�I������

				keyEnableReset();

				int HPX = 300; int HPY = 50;

				DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // ������`�悷��			
				DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // ������`�悷��

				DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // ������`�悷��
				DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // ������`�悷��


				if (item_have_list[kasol2Target + 1].have_kosuu > 0) {
					item_have_list[kasol2Target + 1].have_kosuu = item_have_list[kasol2Target + 1].have_kosuu - 1;

					if (kasol2Target == 0) {
						healflag = 1;
						healti = 5;
						heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + healti;

					}

					if (kasol2Target == 1) {
						healflag = 1;
						healti = 2;
						heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + healti;
					}

				}

				if (item_have_list[kasol2Target + 1].have_kosuu <= 0) {
					item_have_list[kasol2Target + 1].have_kosuu = 0;
				}

			}

		}


		if (mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) {

			itemList(soubihin, soubiSyoji,1);
		} // end


		// �������̓{�^������
		if ((mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) && key_remain > 0) {


			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

				whatuse = itemHairetu[selecting_item - 1]; // 

				key_remain = 0;

				if (whatuse == -99) {
					break; // 		
				}

				if (mode_scene == MODE_ITEM_MENU) {
					mode_scene = MODE_ITEM_WHOM; // 		
				}

				nyuuryokuMatiZ = waitTime1;
				keyEnableZ = 0;
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
				//MessageBox(NULL, TEXT("X��������܂����B"), TEXT("�L�[�e�X�g"), MB_OK);

				mode_scene = MODE_ITEM_TYPE;

				nyuuryokuMatiX = waitTime1;
				key_remain = 1;
				keyEnableReset();
			}


			// �J�[�\������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
					keyEnableUp = 0;

					nyuuryokuMatiUD = waitTime1;
					nyuuryokuMatiUp = waitTime1;
					nyuuryokuMatiDown = waitTime1;

					// �ʂ̏���
					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item - 2; // �������ƂɈႤ

					// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱�� if���̊O�ɏo���Ȃ��̂�
					item_select();
					moving = 0;
				}
			}


			// �J�[�\�������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
					keyEnableDown = 0;

					nyuuryokuMatiUD = waitTime1;
					nyuuryokuMatiUp = waitTime1;
					nyuuryokuMatiDown = waitTime1;

					// �ʂ̏���

					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item + 2; // �������ƂɈႤ

					// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱��
					item_select();
					moving = 0;
				}
			}


			// �L�������E�Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {
					keyEnableRight = 0;

					nyuuryokuMatiLR = waitTime1;
					nyuuryokuMatiLeft = waitTime1;
					nyuuryokuMatiRight = waitTime1;

					//
					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item + 1; // �������ƂɈႤ

					// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱��
					item_select();
					moving = 0;
				}

			}

			// ���Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
					keyEnableLeft = 0;

					nyuuryokuMatiLR = waitTime1;
					nyuuryokuMatiLeft = waitTime1;
					nyuuryokuMatiRight = waitTime1;

					//
					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item - 1; // �������ƂɈႤ

					// ����̓��t�@�N�^�����ɃJ�b�R���ɓ��ꂽ�܂܂ɂ��邱��
					item_select();
					moving = 0;
				}
			}

		}


		if (mode_scene == MODE_ITEM_WHOM) {
			if (healflag == 1) {
				waitheal = waitheal - 1;
			}
			if (waitheal <= 100 && waitheal > 0 ) {

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

					tempVal = partyNarabijyun[whomTargetID1];

					if (heros_def_list[tempVal].heros_hp < heros_def_list[tempVal].heros_hp_max) {
						if (item_have_list[whatuse].have_kosuu <= 0) {
							mode_scene = MODE_ITEM_MENU;

						}

						healti = 5; healflag = 1; waitheal = 120;
						heros_def_list[tempVal].heros_hp = heros_def_list[tempVal].heros_hp + healti;


						healkioku = partyNarabijyun[whomTargetID1];

						if (heros_def_list[tempVal].heros_hp > heros_def_list[tempVal].heros_hp_max) {
							heros_def_list[tempVal].heros_hp = heros_def_list[tempVal].heros_hp_max;
						}

						item_have_list[whatuse].have_kosuu = item_have_list[whatuse].have_kosuu - 1;

					}
				}


				// �ŏ����̌���
				if (whatuse == 2) {

					// MessageBox(NULL, TEXT("���܃R�R1"), TEXT("���b�Z�[�W"), MB_OK);
					if (heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp < heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp_max) {

						if (item_have_list[whatuse].have_kosuu <= 0) {
							mode_scene = MODE_ITEM_MENU;

							break;
						}

						healti = 1; healflag = 1;

						heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp + healti;

						healkioku = partyNarabijyun[whomTargetID1];

						if (heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp > heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp_max) {
							heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[whomTargetID1].heros_hp_max;
						}

						item_have_list[whatuse].have_kosuu = item_have_list[whatuse].have_kosuu - 1;

					}

				}


				// �s�����̔��̌���
				if (whatuse == 3) {

					heros_def_list[partyNarabijyun[whomTargetID1]].heros_HP0_flag = 0;

					heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp + 3;

					//MessageBox(NULL, TEXT("���܃R�Raaaa"), TEXT("���b�Z�[�W"), MB_OK);


					if (item_have_list[whatuse].have_kosuu <= 0) {
						mode_scene = MODE_ITEM_MENU;
	
					}

					if (heros_def_list[whomTargetID1].heros_hp > heros_def_list[whomTargetID1].heros_hp_max) {
						heros_def_list[whomTargetID1].heros_hp = heros_def_list[whomTargetID1].heros_hp_max;
					}

					item_have_list[whatuse].have_kosuu = item_have_list[whatuse].have_kosuu - 1;

				}

				if (item_have_list[whatuse].have_kosuu <= 0) {
					item_have_list[whatuse].have_kosuu = 0;
				}

				nyuuryokuMatiX = waitTime1;
				nyuuryokuMatiZ = waitTime1;
			}


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

			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

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


			if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {

				filterFlag = 0;
				mode_scene = MODE_MENU;

				nyuuryokuMatiX = waitTime1;
				key_remain = 0;
				keyEnableReset();
			}


			if (CheckHitKey(KEY_INPUT_UP) == 1) {

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


			if (CheckHitKey(KEY_INPUT_DOWN) == 1) {

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


			int StatsHPbaseX = 130;
			int StatsHPbaseY = 130;
			int offsetY = 120;


			// �w�i�̐�
			window1Draw(10, 100, 350, 300 + 40);

			// �J�[�\��
			if (mode_scene == MODE_EQUIP_EDIT) {
				tenmetu(90, (110 + 20) + 20 * (whatedit), 300 - 10,
					(110 + 20) + 20 * (1 + whatedit));
			}
			if (mode_scene == MODE_EQUIP_EDIT2) {
				tenmetuStop(90, (110 + 20) + 20 * (whatedit), 300 - 10,
					(110 + 20) + 20 * (1 + whatedit));
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

				locType = soubiOffset + whatedit;
				/*
				// ���L�͏�L�̃��t�@�N�^

				if (whatedit == 0) {
					locType = wepoType;
				}
				if (whatedit == 1) {
					locType = tateType;
				}
				if (whatedit == 2) {
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


						mode3_scene = whatedit + 11; // �����i�f�[�^�x�[�X��11�Ԃ���
						whatedit2 = heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubiKasol[mode3_scene];
					}


					if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1 && mode_scene == MODE_EQUIP_EDIT) {

						filterFlag = 0;
						mode_scene = MODE_EQUIP_MAIN;
						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {

						// MessageBox(NULL, TEXT("�オ������܂����B"),
					// TEXT("�L�[�e�X�g"), MB_OK);
						whatedit = whatedit - 1;

						if (whatedit >= 5) {
							whatedit = 5;
						}
						else if (whatedit < 01) {
							whatedit = 0;
						}

						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {

						// MessageBox(NULL, TEXT("����������܂����B"),
						// TEXT("�L�[�e�X�g"), MB_OK);
						whatedit = whatedit + 1;

						if (whatedit >= 5) {
							whatedit = 5;
						}
						else if (whatedit < 0) {
							whatedit = 0;
						}

						keyEnableReset();
					}

				}

			}


			int sentakuKougekiR = 0; //(soubihin[itemHairetu[whatedit2]].Stype[wepoType]).equipPower[kougekiPara];

			if (mode_scene == MODE_EQUIP_EDIT2) {

				if (CheckHitKey(KEY_INPUT_X) == 1) {

					filterFlag = 0;

					heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubiKasol[mode3_scene ] = whatedit2;

					
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
				locType =  mode3_scene;
	
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


					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {

						// MessageBox(NULL, TEXT("�オ������܂����B"),
					// TEXT("�L�[�e�X�g"), MB_OK);
						whatedit2 = whatedit2 - 1;

						if (whatedit2 >= 5) {
							whatedit2 = 5;
						}
						else if (whatedit2 < 01) {
							whatedit2 = 0;
						}

						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {

						whatedit2 = whatedit2 + 1;

						if (whatedit2 >= 5) {
							whatedit2 = 5;
						}
						else if (whatedit2 < 0) {
							whatedit2 = 0;
						}

						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1
						&& mode_scene == MODE_EQUIP_EDIT2) {

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
			if (CheckHitKey(KEY_INPUT_X) == 1) {
				mode_scene = MODE_MENU;
				keyEnableX = 1; // �g���I������̂Ń[���ɖ߂� // 0�ł͂Ȃ�1�ɂ��Ȃ��ƃo�O
				nyuuryokuMatiX = waitTime1;

				DrawFormatString(250, 250 + 50 * 2, GetColor(255, 255, 255), "���Z����߂�"); // ������`�悷��

			}
		}

		key_remain = 1;

		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}



	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}