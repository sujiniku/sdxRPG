#include "DxLib.h"




#include <stdio.h> // �Z�[�u�p
#pragma warning(disable:4996) // fopen



#include <math.h>  // �؂�グ�v�Z�Ŏg�p






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





int xPosi = 2;
int yPosi = 2;



int moving = 0; //�L�����`�b�v�摜���ړ����Ȃ�0

int keyFlagUp = 0;
int keyFlagDown = 0;
int keyFlagRight = 0;
int keyFlagLeft = 0;

int keyFlagUpRight = 0;

int keyFlagX = 0;
int keyFlagZ = 0;


int nyuuryokuMatiLR = 30;
int nyuuryokuMatiUD = 30;

int nyuuryokuMatiX = 30;
int nyuuryokuMatiZ = 30;


int waitKasol = 30;


int kasol2Target = 0;
int kasol3Target = 0;



int tempHandle;
int destMovable;


enum direction { upward, rightward, downward, leftward };
enum direction hero1_direction = downward;

enum mode { MODE_OP, MODE_LOAD, MODE_INITIAL, MODE_MAP, 
	
	MODE_TOWN, 
	
	MODE_Shop_Main, MODE_Shop_weapon_main, MODE_Shop_weapon_buy	, MODE_Shop_weapon_sell, MODE_Shop_weapon_buyOld,
	MODE_Shop_armor_main, MODE_Shop_armor_buy, MODE_Shop_armor_sell, MODE_Shop_armor_buyOld, 
	MODE_Shop_akusesari_main, MODE_Shop_item_main,
	
	MODE_MENU, 
	
	MODE_narabikae_select1, MODE_narabikae_select2,
	
	MODE_ITEM_TYPE, MODE_ITEM_MENU, MODE_ITEM_MENU_FRONT	,
	MODE_ITEMweapon_MENU, MODE_ITEMweapon_MENU_FRONT, MODE_ITEM_WHOM, MODE_ITEM_WHOM_FRONT, 
	
	MODE_EQUIP_MAIN,	MODE_EQUIP_EDIT, MODE_EQUIP_EDIT2,
	MODE2_EQUIP_HAND, MODE2_EQUIP_SHIELD, MODE2_EQUIP_HELM, MODE2_EQUIP_ARMOR,
	
	MODE_SAVE_MENU, MODE_saving_Now,
	
	MODE_BATTLE_COMMAND, MODE_BATTLE_NOW, MODE_BATTLE_WIN, BATTLE_Agility_proc,

	MODE_Guild_Main, MODE_Guild_Responce, MODE_Guild_Remove,
	
	itemModeMain, itemModeTarget, skillMode,
 };
enum mode mode_scene = MODE_MAP;



int yakusouKosuu = 5;
int dokukesiKosuu = 3;
int soesiKosuu = 4;











int NaraSele1 = 0;

int NaraSele2 = 0;


int uketKyara = 1; // �퓬���ŁA���l�ڂ��_���[�W�󂯂Ă邩�B�u1�v��1�l�ځB

int pageSyori = 0;


// �A�C�e����ޔԍ�
int siyouType = 0;
int wepoType = 1;
int tateType = 2;
int kabutoType = 3;

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


// �����p�[�e�B�\���� (�����X�^�[�\���̗̂��p)
struct heros_def
{
	int heros_id;
	TCHAR heros_name[MAX_LENGTH];
	int heros_hp;
	int heros_hp_max;
	int heros_agility;

	int heros_gold; // �E�B�U�[�h���B�݂����Ɋe�L�������ƂɃS�[���h�����Ă�悤�ɂȂ��Ă�B
	int heros_exp;

	int heros_HP0_flag;

	int PartyIn;


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

};



enum next_attack_flag { next_is_hero, next_is_enemy };
enum next_attack_flag next_attack_var = next_is_hero;


static int encount_monters_id = 1;


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

static int 
;


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





// �퓬�ւ̓˓��̏��� // �̂��̃}�b�v����ŌĂт����̂ŁA�퓬�˓��ƃ}�b�v����̏����͌Œ�̂��ƁB
void battle_start() {

	// MessageBox(NULL, TEXT("battle_enemy_start�ɂ���B"), TEXT("�L�[�e�X�g"), MB_OK);

	// �ȉ��A��^��
	key_remain = 0;

	monster_hp = monster_def_list[encount_monters_id - 1].mon_hp_max;

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

		// hikaeNinzu = tourokuNakama - skip;
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
		// pre_guild(hWnd);


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
		}


	}
}




static int hero1_already_attack_flag = 0;
static int enemy_already_attack_flag = 0;

static int battle_key = 1;

static int damage_HeroAttack = 1;
static int damage_EnemyAttack = 0;

void heroside_attack() {

	int pnCommon = partyNarabijyun[actionOrder[globalTempA]];


	if (heros_def_list[pnCommon].heros_HP0_flag == 0) {
		// ��l�������̍U��


		{

			/* �����̎� */
			// wWinMain �Œ�`�ς�


			/* �T�C�R�� */
			damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_bukiKougekiRyoku;

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

}



void enemy_attack() {

	// �G�����̍U��
	{

		/* �����̎� */
		// wWinMain �Œ�`�ς�

		/* �T�C�R�� */
		damage_EnemyAttack = rand() % (6 / 2) + 0 + 2 * monster_def_list[encount_monters_id - 1].mon_attackPower;

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
			} // heros_def_list[partyNarabijyun[temp]].
		}


	}
	// MessageBox(NULL, TEXT("���܂����B"), TEXT("�L�[�e�X�g"), MB_OK);



}



char strCount[64];
























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







	// mode_scene = MODE_OP;










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



	//����̒�`
	// �v�Z�ʂ�2�掞�Ԃ̃A���S���Y�������ǁA�Ƃ肠�����ҏW����o�O�ϐ���D�悵�A�v�Z���Ԃ͍l�����Ȃ��B
	// �ǂ����Ă��v�Z���Ԃ�Z�k�������Ȃ�Aif��switch-break�ɒu��������΁A�ǂݍ��ݎ��Ԃ��኱�A���点�邩�B
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			weapon_def_list[temp].def_id = 0;
			lstrcpy(weapon_def_list[temp].def_name, TEXT("--------"));
			weapon_def_list[temp].material = mateNothing;
			weapon_def_list[temp].equip_type = typeNothing;
			weapon_def_list[temp].equipPower = 0; // �U����
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			weapon_def_list[temp].def_id = 1;
			lstrcpy(weapon_def_list[temp].def_name, TEXT("�S�̑�"));
			weapon_def_list[temp].material = mateIron;
			weapon_def_list[temp].equip_type = spear;
			weapon_def_list[temp].equipPower = 107; // �U����	
			continue;
		}

		if (temp == 2) {
			weapon_def_list[temp].def_id = 2;
			lstrcpy(weapon_def_list[temp].def_name, TEXT("�S�̃��C�X"));
			weapon_def_list[temp].material = mateIron;
			// weapon_def_list[temp].equip_type = spear;
			weapon_def_list[temp].equipPower = 44; // �U����
			continue;
		}


	}


	//�h��̒�` �^�e
// �v�Z�ʂ�2�掞�Ԃ̃A���S���Y�������ǁA�Ƃ肠�����ҏW����o�O�ϐ���D�悵�A�v�Z���Ԃ͍l�����Ȃ��B
// �ǂ����Ă��v�Z���Ԃ�Z�k�������Ȃ�Aif��switch-break�ɒu��������΁A�ǂݍ��ݎ��Ԃ��኱�A���点�邩�B
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			shield_def_list[temp].def_id = temp;
			lstrcpy(shield_def_list[temp].def_name, TEXT("--------"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 0; // �U����
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			shield_def_list[temp].def_id = temp;
			lstrcpy(shield_def_list[temp].def_name, TEXT("�؂̏�"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 5; // �U����	
			continue;
		}

		if (temp == 2) {
			shield_def_list[temp].def_id = temp;
			lstrcpy(shield_def_list[temp].def_name, TEXT("�S�̏�"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 10; // �U����
			continue;
		}
	}



	//�h��̒�` �J�u�g
// �v�Z�ʂ�2�掞�Ԃ̃A���S���Y�������ǁA�Ƃ肠�����ҏW����o�O�ϐ���D�悵�A�v�Z���Ԃ͍l�����Ȃ��B
// �ǂ����Ă��v�Z���Ԃ�Z�k�������Ȃ�Aif��switch-break�ɒu��������΁A�ǂݍ��ݎ��Ԃ��኱�A���点�邩�B
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			helm_def_list[temp].def_id = temp;
			lstrcpy(helm_def_list[temp].def_name, TEXT("--------"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 0; // �U����
			continue; // �v�Z���Ԃ̐ߖ�̂���
		}

		if (temp == 1) {
			helm_def_list[temp].def_id = temp;
			lstrcpy(helm_def_list[temp].def_name, TEXT("�؂̖X�q"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 5; // �U����	
			continue;
		}

		if (temp == 2) {
			helm_def_list[temp].def_id = temp;
			lstrcpy(helm_def_list[temp].def_name, TEXT("�S�̃J�u�g"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 10; // �U����
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

		weapon_have_list[temp].have_def_id = temp + 1;

		if (temp == 0) {
			weapon_have_list[temp].have_kosuu = 0;
		}

		if (temp == 1) {
			weapon_have_list[temp].have_kosuu = 0;
		}

		if (temp == 2) {
			weapon_have_list[temp].have_kosuu = 0;
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
			monster_def_list[temp].mon_hp_max = 125;
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
			heros_def_list[temp].heros_hp = 32; // 20;
			heros_def_list[temp].heros_hp_max = 25;
			heros_def_list[temp].heros_agility = 56;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;


			heros_def_list[temp].heros_weapon1 = 1;

			heros_def_list[temp].heros_shield = 2;
			heros_def_list[temp].heros_bukiKougekiRyoku = weapon_def_list[heros_def_list[temp].heros_weapon1].equipPower;

		}

		if (temp == 1) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("�s�G�|��"));
			heros_def_list[temp].heros_hp = 108; //  18;
			heros_def_list[temp].heros_hp_max = 18;
			heros_def_list[temp].heros_agility = 100;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;


			heros_def_list[temp].heros_weapon1 = 2;
			heros_def_list[temp].heros_shield = 0;

			heros_def_list[temp].heros_bukiKougekiRyoku = weapon_def_list[heros_def_list[temp].heros_weapon1].equipPower;

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



		// �}�b�v�`��
		for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)
		{
			for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw)
			{
				if (map1table[y_mapDraw][x_mapDraw] == 0) {
					DrawGraph(30 * x_mapDraw, 30 * y_mapDraw, mapchip1Handle, false);
				}
				if (map1table[y_mapDraw][x_mapDraw] == 1) {
					DrawGraph(30 * x_mapDraw, 30 * y_mapDraw, mapchip2Handle, false);
				}
			}

		}


		DrawGraph(30 * monPosiX, 30 * monPosiY, monchipDownHandle, false);



		// �L�����`�b�v�`��
		{
			if (xPosi == monPosiX && yPosi == monPosiY) {


				// �����X�^�[�摜 �N���[���m
				DrawGraph(30 * monPosiX , 30 * monPosiY, blackchipHandle, false);

				//DrawGraph(30 * monPosiX + 50, 30 * monPosiY, monchipDownHandle, true);


			}



			// �ʂ̌����̉摜�ŏ㏑��
			if (hero1_direction == rightward) {
				tempHandle = charachipRightHandle;

				// �O��
				if (nyuuryokuMatiLR > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi, tempHandle, false);
				}

				// ����
				if (nyuuryokuMatiLR <= 20 && nyuuryokuMatiLR > 10) {
					DrawGraph(30 * xPosi + 10, 30 * yPosi, tempHandle, false);
				}

				// �㔼
				if (nyuuryokuMatiLR <= 10 && nyuuryokuMatiLR >= 1) {
					DrawGraph(30 * xPosi + 20, 30 * yPosi, tempHandle, false);
				}
			}

			if (hero1_direction == leftward) {

				if (nyuuryokuMatiLR > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi, charachipLeftHandle, false);
				}

				if (nyuuryokuMatiLR <= 20 && nyuuryokuMatiLR > 10) {
					DrawGraph(30 * xPosi - 10, 30 * yPosi, charachipLeftHandle, false);
				}


				if (nyuuryokuMatiLR <= 10 && nyuuryokuMatiLR >= 1) {
					DrawGraph(30 * xPosi - 20, 30 * yPosi, charachipLeftHandle, false);
				}

			}



			if (hero1_direction == downward) {

				if (nyuuryokuMatiUD > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi - 0, charachipDownHandle, false);
				}

				if (nyuuryokuMatiUD <= 20 && nyuuryokuMatiUD > 10) {
					DrawGraph(30 * xPosi, 30 * yPosi + 10, charachipDownHandle, false);
				}


				if (nyuuryokuMatiUD <= 10 && nyuuryokuMatiUD >= 1) {
					DrawGraph(30 * xPosi, 30 * yPosi + 20, charachipDownHandle, false);
				}

			}


			if (hero1_direction == upward) {

				if (nyuuryokuMatiUD > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi + 0, charachipUpHandle, false);
				}

				if (nyuuryokuMatiUD <= 20 && nyuuryokuMatiUD > 10) {
					DrawGraph(30 * xPosi, 30 * yPosi - 10, charachipUpHandle, false);
				}


				if (nyuuryokuMatiUD <= 10 && nyuuryokuMatiUD >= 1) {
					DrawGraph(30 * xPosi, 30 * yPosi - 20, charachipUpHandle, false);
				}

			}

		}


		if (mode_scene == MODE_MAP) {
			// �ړ��L�[�̃t���O����
			{
				// �L�������E�Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyFlagRight == 0 && moving == 0) {
						if (map1table[yPosi][xPosi + 1] == 1) { destMovable = 0; }
						if (map1table[yPosi][xPosi + 1] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = rightward;
							keyFlagRight = 1;
							nyuuryokuMatiLR = 30;
						}
					}
					// �J�E���g����
					if (keyFlagRight == 1 && nyuuryokuMatiLR > 0) {
						nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
					}
					// �ړ��̏I������
					if (keyFlagRight == 1 && nyuuryokuMatiLR <= 0) {
						keyFlagRight = 0;
						nyuuryokuMatiLR = 30;
						xPosi++;                       // �E��1�}�X�����ړ�
						moving = 0;
					}
				}

				// ���Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyFlagLeft == 0 && moving == 0) {
						if (map1table[yPosi][xPosi - 1] == 1) { destMovable = 0; }
						if (map1table[yPosi][xPosi - 1] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = leftward;
							keyFlagLeft = 1;
							nyuuryokuMatiLR = 30;
						}
					}
					// �J�E���g����
					if (keyFlagLeft == 1 && nyuuryokuMatiLR > 0) {
						nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
					}
					// �ړ��̏I������
					if (keyFlagLeft == 1 && nyuuryokuMatiLR <= 0) {
						keyFlagLeft = 0;
						nyuuryokuMatiLR = 30;
						xPosi--;                       // ����1�}�X�����ړ�
						moving = 0;
					}

				}


				// ���Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
						if (map1table[yPosi + 1][xPosi] == 1) { destMovable = 0; }
						if (map1table[yPosi + 1][xPosi] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = downward;
							keyFlagDown = 1;
							nyuuryokuMatiUD = 30;
						}
					}
					// �J�E���g����
					// keyFlag�͕ʂ̃u���b�N�ŗ��p���Ă�̂ŁA�K�� moving ==1 ���K�v
					if (keyFlagDown == 1 && nyuuryokuMatiUD > 0 && moving == 1) {
						nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
					}
					// �ړ��̏I������
					if (keyFlagDown == 1 && nyuuryokuMatiUD <= 0) {
						keyFlagDown = 0;
						nyuuryokuMatiUD = 30;
						yPosi++;                       // ����1�}�X�����ړ�
						moving = 0;
					}
				}


				// ��Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
						if (map1table[yPosi - 1][xPosi] == 1) { destMovable = 0; }
						if (map1table[yPosi - 1][xPosi] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = upward;
							keyFlagUp = 1;
							nyuuryokuMatiUD = 30;
						}
					}
					// �J�E���g����

					// keyFlag�͕ʂ̃u���b�N�ŗ��p���Ă�̂ŁA�K�� moving ==1 ���K�v
					if (keyFlagUp == 1 && nyuuryokuMatiUD > 0 && moving == 1) {
						nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
					}
					// �ړ��̏I������
					if (keyFlagUp == 1 && nyuuryokuMatiUD <= 0 && moving == 1) {
						keyFlagUp = 0;
						nyuuryokuMatiUD = 30;
						yPosi--;                       // ���1�}�X�����ړ�
						moving = 0;
					}
				}


				// �����X�^�[�����̃G���J�E���g����
				{
					int monMesX = 400; int monMesY = 350; // ���b�Z�[�W���̕\���ʒu

					



					if (xPosi == monPosiX && yPosi == monPosiY) {
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

					//DrawFormatString(400, 350, GetColor(255, 255, 255), "hhhh�����X�^�[�����ꂽ������"); // ������`�悷��

				} // �����X�^�[��������

			}

			// ���j���[����̋A�菈���̂���

			{
				if (nyuuryokuMatiX > 0) {
					nyuuryokuMatiX = nyuuryokuMatiX - 1;
				}

				if (nyuuryokuMatiX <= 0) {
					nyuuryokuMatiX = 0;
				}
			}

			// if �c��ҋ@���[���ŁA�����X�{�^���������ꂽ��Athen ���j���[��ʂɑJ��
			if (CheckHitKey(KEY_INPUT_X) == 1 && mode_scene == MODE_MAP && keyFlagX == 0 && nyuuryokuMatiX == 0) {
				keyFlagX = 1;
				mode_scene = MODE_MENU;
				nyuuryokuMatiX = 30;
			}


			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��

		} // map ���[�h�̏I���


		if (mode_scene == MODE_MENU) {
			int HPX = 300; int HPY = 50;

			// �E�B���h�E��
			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);


			DrawFormatString(HPX +20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // ������`�悷��			
			DrawFormatString(HPX +20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // ������`�悷��


			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // ������`�悷��
			DrawFormatString(HPX + 20, HPY + 20 * (3+1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // ������`�悷��




			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			//DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", x, y); // ������`�悷��


			if (keyFlagX == 1) {

				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "�J�E���g %d", nyuuryokuMatiX); // ������`�悷��
				nyuuryokuMatiX = nyuuryokuMatiX - 1;
			}

			if (nyuuryokuMatiX <= 0) {

				nyuuryokuMatiX = 0;

			}



			if (CheckHitKey(KEY_INPUT_X) == 0 && keyFlagX == 1 && nyuuryokuMatiX == 0) {
				keyFlagX = 2; // �}�b�v�ɖ߂邽�߂�x�{�^���̓��͉\���
				DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��
				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "X��t�\"); // ������`�悷��
			}



			if (keyFlagX == 2) {
				// �J�[�\��
					DrawBox(100, 250 + (selecting_mainmenu -1) * 40, 100 + 80, 250 + (selecting_mainmenu - 1) * 40 +40,
						GetColor(250, 150, 150), 1);

					// �R�}���h��
				DrawFormatString(100+20, 250, GetColor(255, 255, 255), "����"); // ������`�悷��
				DrawFormatString(100+20, 250 + 40, GetColor(255, 255, 255), "����"); // ������`�悷��



				// �\���L�[���͎�

				// �J�[�\������Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
						//if (map1table[y - 1][x] == 1) { destMovable = 0; }
						//if (map1table[y - 1][x] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						//if (destMovable == 1) {
							moving = 1;
							//hero1_direction = upward;
							keyFlagUp = 1;
							waitKasol = 20;
						//}
					}
					// �J�E���g����
					if (keyFlagUp == 1 && waitKasol > 0) {
						waitKasol = waitKasol - 1;
					}
					// �ړ��̏I������
					if (keyFlagUp == 1 && waitKasol <= 0) {
						keyFlagUp = 0;
						waitKasol = 30;
						selecting_mainmenu--;                       // ���1�}�X�����ړ�
						moving = 0;
					}


					if (selecting_mainmenu < 0) {
						selecting_mainmenu = 0;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}
					moving = 0;
				}




				// �J�[�\�������Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
						//if (map1table[y + 1][x] == 1) { destMovable = 0; }
						//if (map1table[y + 1][x] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						//if (destMovable == 1) {
							moving = 1;
							//hero1_direction = downward;
							keyFlagDown = 1;
							waitKasol = 20;
						//}
					}
					// �J�E���g����
					if (keyFlagDown == 1 && waitKasol > 0) {
						waitKasol = waitKasol - 1;
					}
					// �ړ��̏I������
					if (keyFlagDown == 1 && waitKasol <= 0) {
						keyFlagDown = 0;
						waitKasol = 20;
						selecting_mainmenu++;                       // ����1�}�X�����ړ�
						moving = 0;
					}


					if (selecting_mainmenu < 1) {
						selecting_mainmenu = 1;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}

					moving = 0;


				}


				if (CheckHitKey(KEY_INPUT_Z) == 1) {

					if (selecting_mainmenu == 1) {
						mode_scene = itemModeMain;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "�����I�т܂���������"); // ������`�悷��
						nyuuryokuMatiZ = 30;
						keyFlagZ = 0;
					}

					if (selecting_mainmenu == 2) {
						mode_scene = MODE_EQUIP_MAIN;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "������I�т܂���������"); // ������`�悷��
						keyFlagZ = 0;
					}




					if (selecting_mainmenu == 3) {
						MessageBox(NULL, TEXT("���Z���g�����߂̃R�}���h�i���������j�B"), TEXT("�e�X�g"), MB_OK);

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


								// heros_def_list[partyNarabijyun[j]].heros_name
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
									//WideCharToMultiByte(CP_ACP, 0, item_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
									fprintf(fp2, "%s �̌�: %d \n", aaa, item_have_list[temp].have_kosuu);
								}

								// �����i�̕���̏�����
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									//WideCharToMultiByte(CP_ACP, 0, weapon_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
									fprintf(fp2, "%s �̌�: %d \n", aaa, weapon_have_list[temp].have_kosuu);
								}

								// �����i�̏��̏�����
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									//WideCharToMultiByte(CP_ACP, 0, shield_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
									fprintf(fp2, "%s �̌�: %d \n", aaa, shield_have_list[temp].have_kosuu);
								}


								// �����i�̃J�u�g�̏�����
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									//WideCharToMultiByte(CP_ACP, 0, helm_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
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



			if (CheckHitKey(KEY_INPUT_X) == 1 && keyFlagX == 2) {
				mode_scene = MODE_MAP;
				keyFlagX = 0; // �g���I������̂Ń[���ɖ߂� 
				nyuuryokuMatiX = 30;

				DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��

			}


		} // menu �̏I���


		if (mode_scene == itemModeMain) {
			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);



			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // ������`�悷��			
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // ������`�悷��

			// DrawFormatString(HPX +20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // ������`�悷��





			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // ������`�悷��
			DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // ������`�悷��





			int itemWindX = 450;
			int itemWindY = 50;

			// ����̕`��
			DrawBox(itemWindX, itemWindY, itemWindX + 80+40, itemWindY + 180,
				GetColor(100, 100, 250), 1);

			// �J�[�\���`��
			DrawBox(itemWindX, itemWindY + kasol2Target * 40, itemWindX + 80, itemWindY + kasol2Target * 40 + 40,
				GetColor(250, 150, 150), 1);


			DrawFormatString(itemWindX, itemWindY + 40 * 0, GetColor(255, 255, 255), "�� %d", item_have_list[1].have_kosuu); // ������`�悷��
			DrawFormatString(itemWindX, itemWindY + 40 * 1, GetColor(255, 255, 255), "�ŏ����� %d", item_have_list[2].have_kosuu); // ������`�悷��



			// MatiX ������̂̓^�[�Q�b�g�I������̖߂�p
			if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0 ) {
				

				// ����͎g��Ȃ��̂ŁA��������œh��Ԃ����ƂŔ�\���ɂ��Ă���B
				DrawBox(itemWindX, itemWindY, itemWindX + 150, itemWindY + 180,
					GetColor(0, 0, 0), 1);


				mode_scene = MODE_MENU; 
				keyFlagX = 1; // �g���I������̂�1�ɂ��Ȃ��ƃo�O
				nyuuryokuMatiX = 30;

				waitKasol = 30;
				DrawFormatString(250, 250+50, GetColor(255, 255, 255), "�����߂�"); // ������`�悷��


			}


			if (keyFlagZ == 0  && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��


			}
			if (nyuuryokuMatiZ <= 0) {
				nyuuryokuMatiZ = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��


			}

			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��
			}

			if (nyuuryokuMatiX <= 0) {
				nyuuryokuMatiX = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��


			}




			// �f�o�b�O�p
			DrawFormatString(200, 250 + 150 - 50, GetColor(0, 0, 0), "������"); // ������`�悷��
			DrawFormatString(200, 250 + 150 - 50, GetColor(255, 255, 255), "%d",nyuuryokuMatiZ); // ������`�悷��


	


			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyFlagZ == 1) {
				if (kasol2Target==0 && item_have_list[1].have_kosuu >= 1) {

					keyFlagZ = 2;
					nyuuryokuMatiZ = 30;
					mode_scene = itemModeTarget;
				}

				if (kasol2Target == 1 && item_have_list[2].have_kosuu >= 1) {

					keyFlagZ = 2;
					nyuuryokuMatiZ = 30;
					mode_scene = itemModeTarget;
				}


			}

			// �J�E���g����
			if (nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				// �f�o�b�O�p
				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // ������`�悷��
			}

			if (nyuuryokuMatiZ <= 0 && keyFlagZ == 0) {
				keyFlagZ = 1;
				nyuuryokuMatiZ = 0;
			}





			// �\���L�[���͎�

			// �J�[�\������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
					//if (map1table[y - 1][x] == 1) { destMovable = 0; }
					//if (map1table[y - 1][x] == 0) { destMovable = 1; }

					// ����\�Ȃ�t���O�ݒ�
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = upward;
					keyFlagUp = 1;
					waitKasol = 20;
					//}
				}
				// �J�E���g����
				if (keyFlagUp == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// �ړ��̏I������
				if (keyFlagUp == 1 && waitKasol <= 0) {
					keyFlagUp = 0;
					waitKasol = 30;
					kasol2Target--;                       // ���1�}�X�����ړ�
					moving = 0;
				}


				if (kasol2Target < 0) {
					kasol2Target = 0;
				}

				if (kasol2Target >= 3) {
					kasol2Target = 3;
				}

			}




			// �J�[�\�������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
					//if (map1table[y + 1][x] == 1) { destMovable = 0; }
					//if (map1table[y + 1][x] == 0) { destMovable = 1; }

					// ����\�Ȃ�t���O�ݒ�
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = downward;
					keyFlagDown = 1;
					waitKasol = 20;
					//}
				}
				// �J�E���g����
				if (keyFlagDown == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// �ړ��̏I������
				if (keyFlagDown == 1 && waitKasol <= 0) {
					keyFlagDown = 0;
					waitKasol = 20;
					kasol2Target++;                       // ����1�}�X�����ړ�
					moving = 0;
				}


				if (kasol2Target < 0) {
					kasol2Target = 0;
				}

				if (kasol2Target >= 3) {
					kasol2Target = 3;
				}
			}


		}



		if (mode_scene == itemModeTarget) {

			int itemWindX = 450;
			int itemWindY = 50;


			// mode_scene = itemModeTarget;



			// ��������œh��Ԃ��Ĕ�\���ɂ���B
			// DrawBox(350, 50, 350 + 150, 50 + 180,
			//	GetColor(0, 0, 0), 1);

			// keyFlagZ = 1;
			// waitKasol = 20;
			//}

			// �f�o�b�O�p
			DrawFormatString(itemWindX, 250 + 150 - 20, GetColor(255, 255, 255), "kkkkkkk"); // ������`�悷��

			// �J�E���g����
			if (keyFlagZ == 2 && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;
				keyFlagZ = 3;
				// �f�o�b�O�p
				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // ������`�悷��
			}



			if (nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��
			}

			if (nyuuryokuMatiZ <= 0) {
				nyuuryokuMatiZ = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��
			}


			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 50,
				GetColor(150, 150, 255), 1);

			// �J�[�\��
			DrawBox(HPX, HPY + kasol3Target * 60, HPX + 130, HPY + 50 + kasol3Target * 60,
				GetColor(255, 150, 150), 1);






			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // ������`�悷��			
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // ������`�悷��

			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // ������`�悷��
			DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // ������`�悷��







			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��
			}

			if (nyuuryokuMatiX <= 0) {
				nyuuryokuMatiX = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��


			}




						// �\���L�[���͎�

			// �J�[�\������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
					//if (map1table[y - 1][x] == 1) { destMovable = 0; }
					//if (map1table[y - 1][x] == 0) { destMovable = 1; }

					// ����\�Ȃ�t���O�ݒ�
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = upward;
					keyFlagUp = 1;
					waitKasol = 20;
					//}
				}
				// �J�E���g����
				if (keyFlagUp == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// �ړ��̏I������
				if (keyFlagUp == 1 && waitKasol <= 0) {
					keyFlagUp = 0;
					waitKasol = 30;
					kasol3Target--;                       // ���1�}�X�����ړ�
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
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
					//if (map1table[y + 1][x] == 1) { destMovable = 0; }
					//if (map1table[y + 1][x] == 0) { destMovable = 1; }

					// ����\�Ȃ�t���O�ݒ�
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = downward;
					keyFlagDown = 1;
					waitKasol = 20;
					//}
				}
				// �J�E���g����
				if (keyFlagDown == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// �ړ��̏I������
				if (keyFlagDown == 1 && waitKasol <= 0) {
					keyFlagDown = 0;
					waitKasol = 20;
					kasol3Target++;                       // ����1�}�X�����ړ�
					moving = 0;
				}


				if (kasol3Target < 0) {
					kasol3Target = 0;
				}

				if (kasol3Target >= 3) {
					kasol3Target = 3;
				}
			}



			if (CheckHitKey(KEY_INPUT_X) == 1 &&  nyuuryokuMatiX <= 0) {
				keyFlagX = 0;
				keyFlagZ = 0; // �߂�Ŏg���̂Őݒ�

				mode_scene = itemModeMain;
				nyuuryokuMatiX = 30;
			}

			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyFlagZ == 3) {


				// ���s�����ƃJ�E���g�I������
				
					keyFlagZ = 2;
					nyuuryokuMatiZ = 30;
					nyuuryokuMatiX = 0;

					int HPX = 300; int HPY = 50;

					//DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
					//	GetColor(150, 150, 255), 1);


					DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // ������`�悷��			
					DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // ������`�悷��


					DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // ������`�悷��
					DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // ������`�悷��



					if (item_have_list[kasol2Target +1].have_kosuu > 0) {
						item_have_list[kasol2Target + 1].have_kosuu = item_have_list[kasol2Target + 1].have_kosuu - 1;

						if (kasol2Target == 0) {
							
							heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + 5;
						}

						if (kasol2Target == 1) {

							heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + 2;
						}


					}
					if (item_have_list[kasol2Target + 1].have_kosuu <= 0) {
						item_have_list[kasol2Target + 1].have_kosuu = 0;
					}





				// mode_scene = itemModeTarget;

			}




		}











		if (mode_scene == MODE_EQUIP_MAIN) {


			// �O���t�B�b�N�֌W
			{
				// �����̕\����
				// ���C�����[�h�͑����L�����̑I�����[�h�ł���

				// MainGraFrontMenu();

				//BrushBlue_set();

				//BrushPink_set();

				// Rectangle(hdc, 20 + (selecting_mainmenu - 1) * 100, 20,
				//	100 + (selecting_mainmenu - 1) * 100, 70);

				int StatsHPbaseX = 130;
				int StatsHPbaseY = 130;
				int offsetY = 120;


				// �w�i�̐�
				//SelectObject(hdc, blue_thin_1);

				DrawBox(10, 350, 500, 400,
					GetColor(150, 150, 255), 1);

				//Rectangle(hdc, 10, 350, 500, 400);

				//SetBkMode(hdc, TRANSPARENT);
				lstrcpy(mojibuf,
					TEXT("������ύX����L������I��ł��������B"));
				//TextOut(hdc, 15, 350 + 10, mojibuf, lstrlen(mojibuf));
				DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // ������`�悷��



				for (int j = 0; j <= partyNinzuDone - 1; ++j) {
					// �w�i�̐�
					// SelectObject(hdc, blue_thin_1);
					//Rectangle(hdc, 10, 100 + offsetY * j, 300,
					//	200 + offsetY * j);


					DrawBox(10, 100 + offsetY * j, 300, 200 + offsetY * j,
						GetColor(150, 150, 255), 1);


					// �J�[�\��
					if (whomTargetID1 == j) {
						//BrushPink_set();

						//Rectangle(hdc,
						//	10 + 10, 100 + 10 + 120 * (whomTargetID1),
						//	300 - 10, 100 + 70 + 120 * (whomTargetID1));


						DrawBox(10 + 10, 100 + 10 + 120 * (whomTargetID1),
							300 - 10, 100 + 70 + 120 * (whomTargetID1),
							GetColor(255, 150, 150), 1);


					}

					//SetBkMode(hdc, TRANSPARENT);

					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%s"),
						heros_def_list[partyNarabijyun[j]].heros_name);
					//TextOut(hdc, StatsHPbaseX,
					//	StatsHPbaseY - 25 + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));


					DrawFormatString(StatsHPbaseX,
						StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��



					lstrcpy(mojibuf, TEXT("HP"));
					//TextOut(hdc, StatsHPbaseX, StatsHPbaseY + offsetY * j,
					//	mojibuf, lstrlen(mojibuf));

					DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��






					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%d"),
						heros_def_list[partyNarabijyun[j]].heros_hp);
					//TextOut(hdc, StatsHPbaseX + 30,
					//	StatsHPbaseY + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));

					DrawFormatString(StatsHPbaseX + 30,
						StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��




					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("/ %d"),
						heros_def_list[partyNarabijyun[j]].heros_hp_max);
					//TextOut(hdc, StatsHPbaseX + 30 * 2,
					//	StatsHPbaseY + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));



					DrawFormatString(StatsHPbaseX + 30 * 2,
						StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��



					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%d"),
						heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
					//TextOut(hdc, StatsHPbaseX,
					//	StatsHPbaseY + 40 + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));


					DrawFormatString(StatsHPbaseX,
						StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��






					if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag ==
						1) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("�퓬�s�\"));
						//TextOut(hdc, StatsHPbaseX,
						//	StatsHPbaseY + 40 + offsetY * j, mojibuf,
						//	lstrlen(mojibuf));

						DrawFormatString(StatsHPbaseX,
							StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // ������`�悷��




					}


					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("mode: %d"), mode_scene);
					//TextOut(hdc, 130 * 2, 300, mojibuf, lstrlen(mojibuf));

					DrawFormatString(130 * 2, 300, GetColor(255, 255, 255), mojibuf); // ������`�悷��




				}

				// ���̃L�����̑������ڂ̑I�����T�u���[�h
			}// �O���t�B�b�N�֌W


			if (CheckHitKey(KEY_INPUT_Z) == 1 && key_remain ==1) {
			
				key_remain = 0;
				whomTargetID1 = whomCHARA - 1;

				//mode_scene = MODE_EQUIP_EDIT;
				beforeselect = 0;
			
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 ) {

				filterFlag = 0;
				mode_scene = MODE_MENU;

				nyuuryokuMatiX = 30;
				key_remain = 0;
				keyFlagX = 1;
			}

		} // equip ���[�h�̏I���
















		if (mode_scene == skillMode) {
			if (CheckHitKey(KEY_INPUT_X) == 1) {
				mode_scene = MODE_MENU;
				keyFlagX = 1; // �g���I������̂Ń[���ɖ߂� // 0�ł͂Ȃ�1�ɂ��Ȃ��ƃo�O
				nyuuryokuMatiX = 30;

				DrawFormatString(250, 250 + 50*2, GetColor(255, 255, 255), "���Z����߂�"); // ������`�悷��

			}
		}


		


		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}



	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}