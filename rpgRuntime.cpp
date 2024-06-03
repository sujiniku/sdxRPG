#include "DxLib.h"


#include <stdio.h> // セーブ用
#pragma warning(disable:4996) // fopen


#include <math.h>  // 切り上げ計算で使用

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
	{TEXT("ファイア")},
	{TEXT("アイス")}
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

int waitheal = 0; // 回復の表示中の長さ
int damepyon = 0; // 戦闘中にダメージをピョンと動かすアレ
int tekidame = 0; // 敵のダメージ受けてる間だけオン
int mikatadame = 0; // mikataのダメージ受けてる間だけオン

int senkaFlag = 0;

// ウィンドウ色のデフォ値を定数化。カスタム機能をつける場合は別途に新たな変数を用意せよ。
const int wind1R = 50;
const int wind1G = 50;
const int wind1B = 150;

const int window1color = GetColor(wind1R, wind1G, wind1B); // ウィンドウのほか、カーソルのベース色でも使う可能性があるので変数化。
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

const int casolu1R = 250; // l と 1 の区別のため u 追加
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



int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
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
int monPosiX1 = 4; int monPosiY1 = 3; // マップ上でモンスターのいる座標
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


int moving = 0; //キャラチップ画像が移動中なら0

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

// 残骸だけど、検証めんどいので残す
enum mode2 {
	MODE2_EQUIP_UnDef, // 未定義対応
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


int uketKyara = 1; // 戦闘中で、何人目がダメージ受けてるか。「1」で1人目。

int pageSyori = 0;


// アイテム種類番号
const int itemOffset = 10;// 0～9番はシステム処理用に確保
const int siyouType = itemOffset;  // =10

const int soubiOffset = 11; // wepoTypeと同番号だが、拡張性や可読性を考え、別変数を用意

const int wepoType = soubiOffset; // 11
const int tateType = soubiOffset + 1; // 12;
const int kabutoType = soubiOffset + 2; // 13;

int PorEflag[20];

int tempPass = 0;


// これは文字数バッファなど。（モード番号ではない。）
#define MAX_LOADSTRING 100
#define MAX_LENGTH 300 // 要素数に注意 


int afterShop = 0;

int shopAct = 0;

int sinamonoList = 0;

int popFlagTown = 0;
TCHAR popMsg[MAX_LENGTH] = TEXT("aaaa");


const int partymax = 3; // 本当は4だけどテストのため1時的に3
int whatuse = 0;

int beforeselect = 1; // なんらかの選択肢で直前に選んだ選択肢の番号。画面更新用に使う。

int whatedit1 = 0; // 装備コマンドなど、編集をするいろいろな作業用
int whatedit2 = 0; // ひとつの画面内に、前画面用カーソルを残す場合の処理変数


int uwadumeFlag = 1; // 1なら上詰めする。0ならオフ。デバッグモード用 // バグッたら0に戻すこと

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
int enemyAlldeadFlag = 0;// 0なら、敵はまだ全滅してない。1で敵が全滅。

int whoAction = 5; // 0 なら主人公の攻撃。1なら敵の攻撃。試作用のとりあえずのフラグ。

int tourokuMapChip = 2;

int sankaAgility[BATTLE_Agility_proc]; // 素早さ配列
int iremonoAgilityHairetu[BATTLE_Agility_proc]; // 入れ物すばやさ配列
int actionOrder[BATTLE_Agility_proc]; // 行動順配列
int iremonoOrderHairetu[BATTLE_Agility_proc]; // 入れ物こうどうじゅん配列
int mikataAgility[BATTLE_Agility_proc]; // 味方の隊列での素早さ配列。「並び替え」で隊列順が変わるので。
int tekiTairetuAgility[BATTLE_Agility_proc]; // 敵の隊列での素早さ配列。戦闘時のソートで使うので。

// 装備の材質:

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


// グローバル変数:

int IsNewGame = 1; // 初めてこのゲームを起動するとき、1である。一度でもセーブすれば2になる。


int battleTimeFlag = 0; // 戦闘中のコマンド決定後の自動進行に使用。1だと自動進行。0で停止。

enum resource_embedded_flag { on, off };
enum resource_embedded_flag resource_embedded_var = off;


int makeNakamaNinzu = 5; // プログラマーの作った仲間キャラの人数
int tourokuNakama = 4 - 1; // 実際の人数より1少ない // ギルドに登録されてる仲間の人数なので変数


int partyNinzuDone = 2, enemyNinzu = 1;
int partyNinzuTemp = partyNinzuDone;

int sankaNinzu = partyNinzuDone + enemyNinzu;


int hikaeNinzu = 2;


int partyNarabijyun[15] = { 0,1,-1,-1, -1 }; // パーティ隊列の並び替えの処理に使う予定
int partyNarabijyunBefore[15];
int partyNarabijyunAfter[15];



int hikaeNarabijyun[10] = { 2,3,-1, -1, -1 }; // ギルドの処理に使う予定

int monsterNarabijyun[5] = { 0,1,2,3,4 }; // モンスターの戦闘中の行動順の処理に使う予定



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
	int equipPower[20];// 攻撃力や防御力などに使用


};



struct weapon_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// 攻撃力


};


struct shield_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// 攻撃力

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
	int equipPower;// 攻撃力

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
	int equipPower;// 攻撃力


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
int healkioku = 0; // 回復したあと、数秒の表示を記憶するため。


// 味方パーティ構造体 (モンスター構造体の流用)
struct heros_def
{
	int heros_id;
	TCHAR heros_name[MAX_LENGTH];
	int heros_hp;
	int heros_hpdiff;


	int heros_hp_max;
	int heros_agility;

	int heros_gold; // ウィザードリィみたいに各キャラごとにゴールドを持てるようになってる。
	int heros_exp;

	int heros_HP0_flag;

	int PartyIn;

	int heroSoubi[20];
	int heroSoubiKasol[20];

	// 装備品 // 不要
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

	int heros_para[20]; // 攻撃力や守備力の用を合計20、用意。

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


// 戦闘中に使用する変数。 モンスター定義とは別物。
static TCHAR monster_name[30];
static int monster_hp = 10;



static int enemy_alive[2] = { 1, 1 }; // 1なら生きてる。0なら死亡。とりあえず2匹ぶん
// カッコ内は敵の番号。0番から数えている。

static int encount_mons_alive = 1;


HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名


TCHAR mojibuf[MAX_LENGTH] = TEXT("はじめから");


// 装備欄の記述用に、3つbufを確保
TCHAR mojibuf1[MAX_LENGTH] = TEXT("はじめから");
TCHAR mojibuf2[MAX_LENGTH] = TEXT("はじめから");
TCHAR mojibuf3[MAX_LENGTH] = TEXT("はじめから");


void textFunc1(int x, int y) {
	DrawFormatString(x, y, GetColor(255, 255, 255), mojibuf);
}


#define GREEN 10,250,10
void textFuncHeal(int x, int y) {
	DrawFormatString(x, y, GetColor(GREEN), mojibuf);
}



static TCHAR filename_temp[100]; // ファイル読み書きで使う一時的なファイル名


static int mode2_mode_scene = 0;

static int selecting_OP = 1;

static int cursol_stop;
//static 
int your_money = 10000; // これstatic にすると、戦闘終了後にバグる。



static TCHAR drawTalkString1[MAX_LENGTH] = TEXT("temp_talk1"); // 会話欄の1行目
static TCHAR drawTalkString2[MAX_LENGTH] = TEXT("temp_talk2"); // 会話欄の2行目
static TCHAR drawTalkString3[MAX_LENGTH] = TEXT("temp_talk3"); // 会話欄の3行目


static int game_event1_end;
static int game_event2_end;

static int game_event1_end_dummuy;


static int key_remain = 1;


static int chara_x;
static int chara_y;

static int before_chara_x; // 退却処理で1歩前に戻るときに使う。
static int before_chara_y; //


static int start_x = 4;
static int start_y = 3;



// マップのサイズの変数
static int map_x_size = 10;
static int map_y_size = 7;


// 進行先の壁判定のアルゴリズム用の変数
static int desti_x; // 進行先(destination)の壁判定のためのx座標変数 "desiti" means the destination.
static int desti_y; // 進行先の壁判定のためのx座標変数


// maptable の初期化 // 中身はとりあえず0. 安全のため、オーバーフロー時の影響を防ぐ。
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

	int positionX; // その遷移のあるX座標
	int positionY;

	int chara_positionX; // 遷移先マップでのキャラの開始時点でのX座標
	int chara_positionY;

};


// マップ遷移用の構造体変数の作成
static struct MapTrans_def MapTrans_def_list[8];


// map2 のデータ

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

static	int where_map = 1; // 最初のマップ

static int mapTrans_flag_is = 1;


// モンスターの位置。とりあえず2匹ぶん // なおフィールドマップにいる
static int positionX_enemy[5];
static int positionY_enemy[5];

int tekiSuu = 2; // イベント処理用に、このエリアの敵パーティ数を算出。
int gekiha_tekiSuu = 0;


static int TimeCount = 0; // 主に自動進行（敵の行動など）に使用
static int keyCount = 0; // 主にキー入力の時間制限に使用




int dameKei = 0; // ダメージ計算を1回数だけ行うためのフラグ


// アイテムメニューでのカーソル位置の計算用
void item_select() {

	if (selecting_item < 1 || goukeiItem == 0) {
		selecting_item = 1;
	}
	else if (selecting_item > goukeiItem) {
		selecting_item = goukeiItem;
	}

	selecting_item_x = ((selecting_item - 1) % 2) + 1;
	selecting_item_y = ((selecting_item - 1) / 2) + 1;


	// 矢印キーの入力前後でカーソルが同じ位置のままだったら、画面を更新しないための処理
	selecting_itemAfter = selecting_item;


	// 矢印キーの入力前後でカーソルが同じ位置のままだったら、画面を更新しない
	// 画面のチラツキ防止のため

	if (selecting_itemBefore != selecting_itemAfter) {
		//InvalidateRect(hWnd, NULL, FALSE);
		//UpdateWindow(hWnd);
	}
}


// アイテム処理の構造体変数の作成
static struct item_def item_def_list[8]; // アイテム処理の構造体配列の宣言
static struct item_have item_have_list[8];


// 装備品の処理の構造体配列の作成

static struct weapon_def weapon_def_list[15]; // 武器処理の構造体配列の宣言
static struct weapon_have weapon_have_list[15];

static struct shield_def shield_def_list[15]; // シールド処理の構造体配列の宣言
static struct shield_have shield_have_list[15];

static struct helm_def helm_def_list[15]; // カブト処理の構造体配列の宣言
static struct helm_have helm_have_list[15];

static struct armor_def armor_def_list[15]; // ヨロイ処理の構造体配列の宣言
static struct armor_have armor_have_list[15];


// 戦闘遭遇用の構造体変数の作成
static struct monster_def monster_def_list[8];

static struct heros_def heros_def_list[8];


static struct monsterTairetu_def monsterTairetu_def_list[50];

int darkFlag = 0;


void menu_CharaSelectDraw() {

	// 画像の読み込み「image2」は変数名。これが背景フィルター。
	if (filterFlag == 0) {

		//Image image2(L"filter.png");

		// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.

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

		// 背景の青

		window1Draw(winX1, winY1 + offsetY * j,
			winX2, winY2 + offsetY * j);

		if (mode_scene == MODE_ITEM_WHOM) {
			// カーソル
			if (whomTargetID1 == j) {

				tenmetu(winX1, winY1 + offsetY * (whomTargetID1),
					winX2, winY2 + offsetY * (whomTargetID1));

				//MessageBox(NULL, TEXT("デバッグ。"), TEXT("テスト"), MB_OK);

			}
		}


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s fgh"), heros_def_list[partyNarabijyun[j]].heros_name);
		//DrawFormatString(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する
		textFunc1(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j);

		lstrcpy(mojibuf, TEXT("HP"));
		//DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する
		textFunc1(StatsHPbaseX, StatsHPbaseY + offsetY * j);


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_hp);
		// DrawFormatString(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する
		textFunc1(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j);


		int revwait = 120 - waitheal;

		if (healflag == 1 && healkioku == j) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j + 20 - 2 * revwait, GetColor(GREEN), mojibuf); // みどり
			//textFuncHeal(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j + 20 - 2 * revwait);

		}

		if (healflag == 2 && healkioku == j) {

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j - (60) / 6, GetColor(GREEN), mojibuf); // みどり
		   //textFuncHeal(StatsHPbaseX + 30 + 20, StatsHPbaseY - 20 + offsetY * j - (60) / 6);
		}


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[partyNarabijyun[j]].heros_hp_max);
		//DrawFormatString(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する
		textFunc1(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j);

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
		//DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する
		textFunc1(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j);

		if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦闘不能"));
			//DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する
			textFunc1(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j);

		}

	} // end for
}


void menu_CharaSelectDraw2() {


	// 画像の読み込み「image2」は変数名。これが背景フィルター。
	if (filterFlag == 0) {

		//Image image2(L"filter.png");

		// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.

		//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
		filterFlag = 1;
	}


	int shiftTemp = 140;

	int StatsHPbaseX = 130 + shiftTemp; int StatsHPbaseY = 130; // +100 した
	int offsetY = 120;


	for (int j = 0; j <= partyNinzuDone - 1; ++j) {
		// 背景の青

		window1Draw(10 + shiftTemp, 100 + offsetY * j, // +140
			300 + shiftTemp, 200 + offsetY * j);

		if (mode_scene == MODE_ITEM_WHOM) {
			// カーソル
			if (whomTargetID1 == j) {

				tenmetu(10 + 10, 100 + 10 + 120 * (whomTargetID1),
					300 - 10, 100 + 70 + 120 * (whomTargetID1));

				//MessageBox(NULL, TEXT("デバッグ。"), TEXT("テスト"), MB_OK);

			}
		}

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[partyNarabijyun[j]].heros_name);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		lstrcpy(mojibuf, TEXT("HP"));
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_hp);
		DrawFormatString(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[partyNarabijyun[j]].heros_hp_max);
		DrawFormatString(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


		if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦闘不能"));
			DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		}

	}

}


// 戦闘への突入の処理 // のちのマップ判定で呼びだすので、戦闘突入とマップ判定の順序は固定のこと。
void battle_start() {

	// MessageBox(NULL, TEXT("battle_enemy_startにいる。"), TEXT("キーテスト"), MB_OK);

	// 以下、定型文
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


// モンスターとの遭遇判定
void check_encount_enemy(HWND hWnd) {

	if (where_map == 2) {
		for (int i = 0; i <= 1; i = i + 1)
		{
			if (enemy_alive[i] == 1) {
				if (chara_x == positionX_enemy[i] && chara_y == positionY_enemy[i]) {

					encount_monsters_id = i + 1;	// ここに、誰と遭遇したかを記述

					// スライム encount id が 1番
					// コボルと id 2番

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

			// わからんが、たぶん大事なので残す
			// kousinNarabijyun[temp - skip] = partyNarabijyun[temp];
		}

		if (partyNarabijyun[temp] < 0) {

			akiHairetu[skip] = temp;

			skip = skip + 1;
		}
	}

}


void hikaeKeisan() {
	// これが加わる
	int skip = 0; // remove 命令でもskipを流用する。
	{
		for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {

			if (heros_def_list[temp].PartyIn == 0) {
				hikaeNarabijyun[skip] = temp;
				skip = skip + 1; // 代入し終わってから、skipを増やす。次のメンバー用なので。
			}

			if (heros_def_list[temp].PartyIn == 1) {
				// 何もしない
			}

		}

		hikaeNarabijyun[skip] = -1;
	}

}



void pre_guild() {

	//MessageBox(NULL, TEXT("ギルドのテスト中。\n"), TEXT("キーテスト"), MB_OK);

	key_remain = 0;

	whomTargetID1 = 0; whomCHARA = 1;
	whomTargetID1party = 0; whomTargetID1hikae = 0;

	Akihaikeisan();


	// 控えメンバーの配列処理の準備
	{
		if (uwadumeFlag == 1) {

			int skip = 0;
			for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {

				if (heros_def_list[temp].PartyIn == 0) {
					hikaeNarabijyun[skip] = temp;
					skip = skip + 1; // 代入し終わってから、skipを増やす。次のメンバー用なので。
				}

				if (heros_def_list[temp].PartyIn == 1) {
					// 何もしない
				}
			}
			hikaeNarabijyun[skip] = -1;
		}
	}
	mode_scene = MODE_Guild_Main;
}

int townFlag = 0; // これないと、タウンからでても、タウンに入り続ける

void check_encount_town() {


	//if (where_map == 1 && chara_x == town_X && chara_y == town_Y) {
	if (townFlag == 0 && where_map == 1 && xPosi == town_X && yPosi == town_Y) {

		// MessageBox(NULL, TEXT("kansuのテスト中。"), TEXT("キーテスト"), MB_OK);

		popFlagTown = 1;
		lstrcpy(popMsg, TEXT("パーティの編成をできます。"));

		mode_scene = MODE_TOWN;
		// pre_guild(); // のちのちのギルド実装のため残す

	}
}




void check_MapTransition() {
	//MessageBox(NULL, TEXT("マップ遷移の判定にいる。"), TEXT("キーテスト"), MB_OK);

	if (chara_x == MapTrans_def_list[(where_map)-1].positionX && chara_y == MapTrans_def_list[where_map - 1].positionY)
	{
		//MessageBox(NULL, TEXT("マップ遷移の直前にいる。"), TEXT("キーテスト"), MB_OK);		

		chara_x = MapTrans_def_list[where_map - 1].chara_positionX;
		chara_y = MapTrans_def_list[where_map - 1].chara_positionY;

		where_map = MapTrans_def_list[where_map - 1].to_Where_Map; // マップを移動先に上書き

		// 拡張のため残す
		//mapTrans_flag_is = 1; // 移動先にマップ遷移が存在するか


		desti_x = chara_x; // 移動先のリセット		
		desti_y = chara_y;


		// ここから先、移動先のマップ描画のための処理

		// 移動先マップにあるマップ遷移の情報を書く
		MapTrans_position_x = MapTrans_def_list[where_map - 1].positionX;
		MapTrans_position_y = MapTrans_def_list[where_map - 1].positionY;


		// maptableに移動先マップを代入
		int x_map = 0, y_map = 0;

		for (x_map = 0; x_map <= 9; ++x_map)
		{
			for (y_map = 0; y_map <= 6; ++y_map)
			{
				// 代入内容は、移動先マップの代入をすることに注意

				for (int i = 0; i <= tourokuMapChip - 1; ++i) { // 全マップをチェック
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
		// 主人公たちの攻撃

		/* 乱数の種 */
		// wWinMain で定義済み

		/* サイコロ */

		// koudouKiroku[sentouNaninme] = koudouMgk;

		if(koudouKiroku[pnCommon] == koudouAtk) {
			damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_para[kougekiPara];	
		}

		if (koudouKiroku[pnCommon] == koudouMgk) {
				damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_para[kougekiPara] + magic_def_list[magicKiroku[pnCommon]].power ;
		}

		// 
		// 
		// 敵にダメージ
		monster_hp = monster_hp - damage_HeroAttack;

		// モンスターの死亡の処理
		if (monster_hp < 1) {
			monster_hp = 0;

			enemy_alive[(encount_monsters_id)-1] = 0; // フィールド上の敵の除去

			encount_mons_alive = 0; // 現在戦闘中の敵を死亡にフラグ設定

		}
	}
}


void enemy_attack() {
	tekidame = 0;
	damepyon = 0;

	// 敵たちの攻撃
	/* 乱数の種 */
		// wWinMain で定義済み

	int pnCommon = partyNarabijyun[actionOrder[sentoKoudoCount]];

	// ダメージ計算式
	/* サイコロ */
		damage_EnemyAttack = rand() % (6 / 2) + 10 + 2 * monster_def_list[encount_monsters_id - 1].mon_attackPower
			- heros_def_list[partyNarabijyun[0]].heros_para[syubiPara];


	if (damage_EnemyAttack <= 0) {
		damage_EnemyAttack = 0;
	}

	// 隊列1人目にダメージ
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
		// MessageBox(NULL, TEXT("いまfoそこ。"), TEXT("キーテスト"), MB_OK);
		tempVal = partyNarabijyun[temp];

		if (heros_def_list[tempVal].heros_hp < 1) {
			heros_def_list[tempVal].heros_hp = 0;

			// 戦闘不能フラグがオン
			heros_def_list[tempVal].heros_HP0_flag = 1;
		}
	}
	// MessageBox(NULL, TEXT("いまそこ。"), TEXT("キーテスト"), MB_OK);

}





void hikaesai() {
	filterFlag = 1;
	// Draw_map(hdc); // 応急処置。できれば、hbitmapuをグローバル変数にしたいが、方法が分からない。
	// もし処理速度に問題が生じるようなら、背景色を（マップ背景描画をやめて）黒に変更。


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



	int carsoruHigh = 50; // 文字スパンとカーソル高さは同じにすること

	//BrushPink_set(hdc);

	if (mode_scene != MODE_Guild_Main) {
		//BrushDarkPink_set(hdc);
		tenmetuStop(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1hikae),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1hikae)); // あとでダーク化

	}

	if (mode_scene == MODE_Guild_Main) {
		tenmetu(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1hikae),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1hikae));

	}



	int offsetXtemp1 = 30; // カーソル高さと同じなのは偶然。
	int yspan1 = carsoruHigh;

	window1Draw(offsetXtemp1 - 1 * 10, offsetYtemp1 - 20, offsetXtemp1 + 150, offsetYtemp1 + 10);
	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("控えメンバー"));

	// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), GetColor(255, 255, 255), mojibuf); // 文字を描画する


	if (uwadumeFlag == 0) {
		for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {
			if (heros_def_list[temp].PartyIn == 0) {
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[temp].heros_name);
			}

			if (heros_def_list[temp].PartyIn == 1) {
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("出動中: %s"), heros_def_list[temp].heros_name);
			}

			// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, mojibuf, lstrlen(mojibuf));

			DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, GetColor(255, 255, 255), mojibuf); // 文字を描画する


		}


		// temp == tourokuNakama + 1    に相当
		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("【外す】"));
		// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120, mojibuf, lstrlen(mojibuf));

		DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120, GetColor(255, 255, 255), mojibuf); // 文字を描画する


	}


	if (uwadumeFlag == 1) {

		int skip = 0;

		// 控え終わり記号の -1 まで読み込んでるので、読み込み回数は控え人数よりも1回多い
		for (int temp = 0; temp <= hikaeNinzu; temp = temp + 1) { // tempは0から数えてるので、2項目が hikaeNinzu;
		// for (int temp = 0; temp <= 1; temp = temp + 1) { // 2項目が hikaeNinzu;

			if (hikaeNarabijyun[temp] > -1) { // 右辺が0だと主人公が非表示になってしまう

				if (heros_def_list[hikaeNarabijyun[temp]].PartyIn == 0) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s "), heros_def_list[hikaeNarabijyun[temp]].heros_name);
					skip = skip + 1;
				}

				if (heros_def_list[hikaeNarabijyun[temp]].PartyIn == 1) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("編成中: %s"), heros_def_list[hikaeNarabijyun[temp]].heros_name);
				} // デバッグ用にメッセージを「編成」に変えてる。

				// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, mojibuf, lstrlen(mojibuf));

				DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (temp)+120, GetColor(255, 255, 255), mojibuf); // 文字を描画する




			}

		}


		// temp == tourokuNakama + 1    に相当
		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("【外す】"));
		// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (skip)+120, mojibuf, lstrlen(mojibuf));

		DrawFormatString(offsetXtemp1, 30 - 10 + yspan1 * (skip)+120, GetColor(255, 255, 255), mojibuf); // 文字を描画する

	}

	// デバッグ文
	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Hikae[0]: %d"), hikaeNarabijyun[0]);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50, mojibuf, lstrlen(mojibuf));


	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Hikae[1]: %d"), hikaeNarabijyun[1]);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 1, mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 1, GetColor(255, 255, 255), mojibuf); // 文字を描画する


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("控え人数: %d"), hikaeNinzu);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 2, mojibuf, lstrlen(mojibuf));


	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する



	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("whomCH: %d"), whomCHARA);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 3, mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("P人数: %d"), partyNinzuTemp);
	// TextOut(hdc, offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 4, mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1 + 100, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120 - 50 + 20 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する

}



void parsai() {

	// パーティメンバー側も再描画の必要あり

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
		// よく分からんので、テストで確認
	}

	if (mode_scene == MODE_Guild_Remove) {
		//Rectangle(hdc, offsetXtemp2 + 10, offsetYtemp2 + 10 + 60 * (whomTargetID1party),offsetXtemp2 + 150, offsetYtemp2 + kasoruHeight + 10 + 60 * (whomTargetID1party));

		tenmetu(offsetXtemp2 + 10, offsetYtemp2 + 10 + 60 * (whomTargetID1party), offsetXtemp2 + 150, offsetYtemp2 + kasoruHeight + 10 + 60 * (whomTargetID1party));

	}

	int yspan1 = 50;


	window1Draw(offsetXtemp2 + 10, offsetYtemp2 - 20, offsetXtemp2 + 180, offsetYtemp2 + 10);
	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("パーティメンバー"));

	// TextOut(hdc, offsetXtemp2 + 30, -10 + offsetYtemp2 + yspan1 * (0), mojibuf, lstrlen(mojibuf));
	DrawFormatString(offsetXtemp2 + 30, -10 + offsetYtemp2 + yspan1 * (0), GetColor(255, 255, 255), mojibuf); // 文字を描画する





	for (int temp = 0; temp <= partymax - 1; temp = temp + 1) {

		if (partyNarabijyun[temp] >= 0) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[partyNarabijyun[temp]].heros_name);
		}

		if (partyNarabijyun[temp] < 0) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("【空き枠】"));
		}

		//TextOut(hdc, offsetXtemp2 + 30, offsetYtemp2 + 30 + yspan1 * (temp), mojibuf, lstrlen(mojibuf));

		DrawFormatString(offsetXtemp2 + 30, offsetYtemp2 + 30 + yspan1 * (temp), GetColor(255, 255, 255), mojibuf); // 文字を描画する

	}

	// 検索用 aaaaaaaaaaaaa

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

static struct tykou soubihin[20]; // 構造体配列の宣言
static struct tykou* Asoubuhin = &soubihin[20];



struct tykou2 {
	struct soubi_have Stype[10];
};

struct tykou2 soubiSyoji[20]; // 構造体配列の宣言

static struct tykou2* AsoubuSyoji = &soubiSyoji[10];


void itemList(struct tykou soubuhin[10], struct tykou2 soubiSyoji[20], int kasolFlag) {

	// darkFlag = 1;
	darkFlag = 0;

	window1Draw(10, 100, 600, 400);

	// カーソル描画設定
	int spanY = FontYoffset;
	int Y0 = 120;

	// こっちは覗き見なのでカーソルはオフに


	if (kasolFlag == 1) {
		tenmetu(20 + (selecting_item_x - 1) * 300, Y0 + (selecting_item_y - 1) * spanY, 250 + (selecting_item_x - 1) * 300, Y0 + spanY + (selecting_item_y - 1) * spanY);
	}

	goukeiItem = 0;

	int column = 2;

	int xcommon;
	int ycommon;

	// 表示フラグ
	int ViewFlag[10]; // 0はシステム用, 1が使用品, 2が武器、3がタテ、4がカブト

	// int ViewFlagItem = 1;
	// int ViewFlagWeapon = 0;
	// int ViewFlagShield = 0;
	// int ViewFlagHelm = 0;

	if (mode_scene == MODE_ITEMweapon_MENU || mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEM_TYPE) {

		// 安全のため一旦0に

		for (int temp = 1; temp <= 4; temp = temp + 1) {
			ViewFlag[temp] = 0;

		}

		/*
		ViewFlag[1] = 0;  // ViewFlagItem = 0;
		ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
		ViewFlag[3] = 0;  // ViewFlagShield = 0;
		ViewFlag[4] = 0;  // ViewFlagHelm = 0;
		*/


		// 表示フラグ設定
		if (mode_scene == MODE_ITEM_MENU || (selecting_mainmenu == 1 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 1;  // ViewFlagItem = 1;

			for (int temp = 2; temp <= 4; temp = temp + 1) {
				ViewFlag[temp] = 0; // 装備品は表示オフ

			}

			//ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
			//ViewFlag[3] = 0;  // ViewFlagShield = 0;
			//ViewFlag[4] = 0;  // ViewFlagHelm = 0;
		}

		if (mode_scene == MODE_ITEMweapon_MENU || (selecting_mainmenu == 2 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;  // ViewFlagItem = 0;


			for (int temp = 2; temp <= 4; temp = temp + 1) {
				ViewFlag[temp] = 1; // 装備品は表示オン

			}
			//ViewFlag[2] = 1;  // ViewFlagWeapon = 1;
			//ViewFlag[3] = 1;  // ViewFlagShield = 1;
			//ViewFlag[4] = 1;  // ViewFlagHelm = 1;
		}

		if ((selecting_mainmenu == 3 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;   //ViewFlagItem = 0;

			for (int temp = 2; temp <= 4; temp = temp + 1) {
				ViewFlag[temp] = 0; // 装備品は表示オフ

			}

			//ViewFlag[2] = 0;   //ViewFlagWeapon = 0;
			//ViewFlag[3] = 0;   //ViewFlagShield = 0;
			//ViewFlag[4] = 0;   //ViewFlagHelm = 0;
		}

	}

	int LimintTemp = goukeiItem;
	goukeiItem = 0;


	// アイテム配列のクリア。前の残骸が残る場合があるので。
	itemHairetu[0] = -99;


	int itemIDcount = 0; // for文の外で使うので、消したらダメ

	// 使用品の配列代入
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
		} // 使用品の配列代入
	}

	// 
	for (int tempVal1 = 2; tempVal1 <= 4; tempVal1 = tempVal1 + 1) {

		if (ViewFlag[tempVal1]) {

			LimintTemp = goukeiItem;

			// 装備品の配列代入
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
			} // 装備品の配列代入
		}

	}

	itemTypeHairetu[itemIDcount] = -99; // 終了を意味する数。

	// 道具コマンドの道具表示や武器表示など
	{
		for (int temp = 0; temp <= 10; temp = temp + 1) {

			int temp2 = temp + pageSyori * 6;

			if (itemTypeHairetu[temp2] == -99) {
				lstrcpy(mojibuf, TEXT("   "));

				DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する
				break;
			}

			xcommon = 30 + 300 * floor((temp) % column);
			ycommon = 130 + spanY * floor((temp) / column);

			if (itemTypeHairetu[temp2] == siyouType) {
				lstrcpy(mojibuf, item_def_list[itemHairetu[temp2]].def_name);
			}


			int defSoubiType = 2; // 定義し終わった装備品の種類数からマイナス1。 たとえば武器、カテ、カブトなら 3-1=2

			if (itemTypeHairetu[temp2] >= soubiOffset // wepoType
				&& itemTypeHairetu[temp2] <= soubiOffset + defSoubiType // kabutoType
				)
				/* // 意味
				if (itemTypeHairetu[temp2] == soubiOffset // wepoType
				|| itemTypeHairetu[temp2] == soubiOffset +1 // tateType
				|| itemTypeHairetu[temp2] == soubiOffset + 2 // kabutoType
				)
				*/
			{

				int locType;

				locType = itemTypeHairetu[temp2];// 意味は下記コメントの内容	

				/*		// このコメントは上記の説明なので消すな
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

				// 装備品の名前表示セット. まだ個数は表示してない
				lstrcpy(mojibuf, (soubihin[itemHairetu[temp2]].Stype[locType]).def_name);

			}

			DrawFormatString(xcommon, ycommon, GetColor(255, 255, 255), mojibuf);

			// 個数セットのモジュール
			// 個数欄の背景クリア用
			lstrcpy(mojibuf, TEXT("   "));
			DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf);


			if (itemTypeHairetu[temp2] == siyouType) {
				// 道具の個数表示. 表示は後処理のDrawFormat で一括
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
				// 装備品の個数表示. 表示は後処理のDrawFormat で一括
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[itemHairetu[temp2]].Stype[locType]).have_kosuu);
			}

			// 上記代入を実際に表示する
			DrawFormatString(xcommon + 130, ycommon, GetColor(255, 255, 255), mojibuf);

		}
	} // 道具コマンドの道具表示や武器表示など

	itemIDcount = 0;
} // itemlist



bool CheckZetc = CheckHitKey(KEY_INPUT_Z) == 1 && keyEnableZ == 1 && nyuuryokuMatiZ <= 0; // if文で使う

void CheckZetcFunc(void) {
	CheckZetc = CheckHitKey(KEY_INPUT_Z) == 1 && keyEnableZ == 1 && nyuuryokuMatiZ <= 0; // これは更新用

}

bool CheckXetc = CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1 && nyuuryokuMatiX <= 0; // if文で使う
void CheckXetcFunc(void) {
	CheckXetc = CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1 && nyuuryokuMatiX <= 0; // これは更新用

}

bool CheckUPetc = CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp != 1 && nyuuryokuMatiUp <= 0; // if文で使う
void CheckUPetcFunc(void) {
	CheckUPetc = CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && nyuuryokuMatiUp <= 0; // これは更新用

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
struct sinaList hinmoku[5]; // 構造体配列の宣言

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
		DrawFormatString(280, koumoku_Y + 30 + 30 * temp, GetColor(255, 255, 255), mojibuf); // 文字を描画する


		lstrcpy(mojibuf, TEXT("50G"));
		// TextOut(hdc, 280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, mojibuf, lstrlen(mojibuf));

		DrawFormatString(280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, GetColor(255, 255, 255), mojibuf); // 文字を描画する



		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[hinmoku[temp].subID].Stype[hinmoku[temp].Grouptype]).have_kosuu);

		DrawFormatString(280 + 100 * 2 + 50, koumoku_Y + 30 + kasolOffsetY * temp, GetColor(255, 255, 255), mojibuf); // 文字を描画する




	} // for temp 終わり

	if (shopMijissou == 1) {

		int temp = 1;

		lstrcpy(mojibuf, TEXT("未実装"));
		// TextOut(hdc, 280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, mojibuf, lstrlen(mojibuf));

		DrawFormatString(280 + 120, koumoku_Y + 30 + kasolOffsetY * temp, GetColor(255, 255, 255), mojibuf); // 文字を描画する



	}








}






int offsetYtemp1 = 100;


void shopCommon1() {


	int offsetYtemp1 = 100;
	// SelectObject(hdc, blue_thin_1);

	// Rectangle(hdc, 10, offsetYtemp1, offsetYtemp1 + 100, 400);

	window1Draw(10, offsetYtemp1, offsetYtemp1 + 100, 400);


	int carsoruHigh = 50; // 文字スパンとカーソル高さは同じにすること

	// BrushDarkPink_set(hdc);

	if (mode_scene == MODE_Shop_Main || mode_scene == MODE_Shop_weapon_main || mode_scene == MODE_Shop_armor_main) {
		tenmetu(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1)); // 
	}
	else {
		tenmetuStop(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1),
			150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1)); // あとでダークに直す
	}




	int offsetXtemp1 = 30; // カーソル高さと同じなのは偶然。
	int yspan1 = carsoruHigh;


	window1Draw(offsetXtemp1 - 20, offsetYtemp1 - 20, offsetXtemp1 + 70, offsetYtemp1 + 20);

	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("行き先"));
	// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (0), GetColor(255, 255, 255), mojibuf); // 文字を描画する


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("武器"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (1), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (1), GetColor(255, 255, 255), mojibuf); // 文字を描画する


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("防具"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (2), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (2), GetColor(255, 255, 255), mojibuf); // 文字を描画する


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装飾品"));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (3), GetColor(255, 255, 255), mojibuf); // 文字を描画する


	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("道具"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (4), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (4), GetColor(255, 255, 255), mojibuf); // 文字を描画する



	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("出る"));
	//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (5), mojibuf, lstrlen(mojibuf));

	DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (5), GetColor(255, 255, 255), mojibuf); // 文字を描画する

}

int whomtargetID2;

void shopCommand() {

	//lstrcpy(mojibuf, TEXT("武器屋テスト売る。"));
	//TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

	//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


	//SelectObject(hdc, blue_thin_1);
	window1Draw(250, 100,
		480, 150);


	int BuySellX = 280;
	int BuySellY = 120;

	int carsoruHigh = 30;
	int spanX = 50;


	//1; // 「売る」にカーソル

	//BrushDarkPink_set(hdc);

	if (mode_scene == MODE_Shop_Main || mode_scene == MODE_Shop_weapon_main || mode_scene == MODE_Shop_armor_main) {
		tenmetu(BuySellX + spanX * (shopAct), offsetYtemp1 + 10,
			BuySellX + 40 + spanX * (shopAct), offsetYtemp1 + 60); // 
	}
	else {
		tenmetuStop(BuySellX + spanX * (shopAct), offsetYtemp1 + 10,
			BuySellX + 40 + spanX * (shopAct), offsetYtemp1 + 60); // あとでダーク化
	}



	lstrcpy(mojibuf, TEXT("買う"));
	// TextOut(hdc, BuySellX, BuySellY, mojibuf, lstrlen(mojibuf));

	DrawFormatString(BuySellX, BuySellY, GetColor(255, 255, 255), mojibuf); // 文字を描画する


	lstrcpy(mojibuf, TEXT("売る"));
	//TextOut(hdc, BuySellX + spanX * 1, BuySellY, mojibuf, lstrlen(mojibuf));


	DrawFormatString(BuySellX + spanX * 1, BuySellY, GetColor(255, 255, 255), mojibuf); // 文字を描画する


	lstrcpy(mojibuf, TEXT("中古"));
	// TextOut(hdc, BuySellX + spanX * 2, BuySellY, mojibuf, lstrlen(mojibuf));

	DrawFormatString(BuySellX + spanX * 2, BuySellY, GetColor(255, 255, 255), mojibuf); // 文字を描画する



	lstrcpy(mojibuf, TEXT("出る"));
	// TextOut(hdc, BuySellX + spanX * 3, BuySellY, mojibuf, lstrlen(mojibuf));

	DrawFormatString(BuySellX + spanX * 3, BuySellY, GetColor(255, 255, 255), mojibuf); // 文字を描画する


}

// int offsetYtemp1 = 100;

void shopKoumoku() {


	//BrushPink_set(hdc);
	//tenmetu(280, 200 + 60 + 30 * (whomTargetID1),		320 + 40, offsetYtemp1 + 60 + 60 + 30 * (whomTargetID1));

	//SetBkColor(hdc, RGB(0xFF, 0xFF, 0xFF));
	//SetBkMode(hdc, OPAQUE);

	// 見出し
	if (1) {
		lstrcpy(mojibuf, TEXT("商品名"));
		//TextOut(hdc, 280, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280, 200, GetColor(255, 255, 255), mojibuf); // 文字を描画する



		lstrcpy(mojibuf, TEXT("価格"));
		//TextOut(hdc, 280 + 120, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280 + 120, 200, GetColor(255, 255, 255), mojibuf); // 文字を描画する



		lstrcpy(mojibuf, TEXT("在庫"));
		//TextOut(hdc, 280 + 170, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280 + 170, 200, GetColor(255, 255, 255), mojibuf); // 文字を描画する



		lstrcpy(mojibuf, TEXT("所持数"));
		//TextOut(hdc, 280 + 170 + 50, 200, mojibuf, lstrlen(mojibuf));
		DrawFormatString(280 + 170 + 50, 200, GetColor(255, 255, 255), mojibuf); // 文字を描画する

	}

}




void shopGoldRan() {


	//BrushBlue_set(hdc);
	int GoldRanX = 490; int GoldRanY = 50;

	window1Draw(GoldRanX, GoldRanY,
		GoldRanX + 120, 110);


	lstrcpy(mojibuf, TEXT("所持金"));


	DrawFormatString(GoldRanX, GoldRanY + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する



	_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d G"), your_money);

	DrawFormatString(GoldRanX, GoldRanY + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する




}



void shopHinBack() {


	//SelectObject(hdc, blue_thin_1);
	window1Draw(250, 170, 560, 400);

	lstrcpy(mojibuf, TEXT("ここに商品や所持品が表示されます"));
	// TextOut(hdc, 280, 170, mojibuf, lstrlen(mojibuf));

	DrawFormatString(280, 170, GetColor(255, 255, 255), mojibuf); // 文字を描画する


}


void shopData() {

	if (shopMijissou == 1) {
		// 売り物の定義
		// 1品目
		// 非表示
		hinmoku[0].Grouptype = -99;
		hinmoku[0].subID = -99;

	}


	if (whomTargetID1 == 0) {
		// 売り物の定義
		// 1品目
		// strcpy_s(  hinmoku[0].ItemName, 10 ,"毒消し"); 
		hinmoku[0].Grouptype = wepoType;
		hinmoku[0].subID = 1;

		itemHairetu[0] = hinmoku[0].subID;
		itemTypeHairetu[0] = hinmoku[0].Grouptype;

		// 2品目   
		hinmoku[1].Grouptype = wepoType;
		hinmoku[1].subID = 2;
		//strcpy_s( ItemYouso[1][1].ItemName, 10 ,"鉄の剣"); 


		// 3品目   
		hinmoku[2].Grouptype = -99;
		hinmoku[2].subID = -99;
	}

	if (whomTargetID1 == 1) {
		// 売り物の定義
		// 1品目
	// strcpy_s(  hinmoku[0].ItemName, 10 ,"毒消し"); 
		hinmoku[0].Grouptype = tateType;
		hinmoku[0].subID = 1;


		// 2品目   
		hinmoku[1].Grouptype = tateType;
		hinmoku[1].subID = 2;
		//strcpy_s( ItemYouso[1][1].ItemName, 10 ,"鉄の剣"); 


		// 3品目   
		hinmoku[2].Grouptype = kabutoType;
		hinmoku[2].subID = 1;


		// 4品目   
		hinmoku[3].Grouptype = kabutoType;
		hinmoku[3].subID = 2;


		// 5品目   
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






// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定

	// SetUseSoftwareRenderModeFlag(TRUE); // ソフトウェアレンダリングのテスト

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
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











	// アイテムの情報
	int tourokuItem = 3;
	for (int temp = 0; temp <= tourokuItem; temp++) {

		item_def_list[temp].def_id = temp;
		item_def_list[temp].item_type = siyouType;

		if (temp == 0) {
			// 空白の定義
			lstrcpy(item_def_list[temp].def_name, TEXT("--------"));
			item_def_list[temp].healti = 0;
		}

		if (temp == 1) {
			//薬草の定義
			lstrcpy(item_def_list[temp].def_name, TEXT("薬草"));
			item_def_list[temp].healti = 5;
		}

		if (temp == 2) {
			lstrcpy(item_def_list[temp].def_name, TEXT("毒消し草"));
			item_def_list[temp].healti = 1;
		}

		if (temp == 3) {
			lstrcpy(item_def_list[temp].def_name, TEXT("不死鳥の尾")); // 漢字の理由は字数の節約
			item_def_list[temp].healti = 2;
		}
	}



	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			(soubihin[temp].Stype[wepoType]).def_id = 0;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[wepoType]).material = mateNothing;
			(soubihin[temp].Stype[wepoType]).equip_type = typeNothing;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			(soubihin[temp].Stype[wepoType]).def_id = 1;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("鉄の槍"));
			(soubihin[temp].Stype[wepoType]).material = mateIron;
			(soubihin[temp].Stype[wepoType]).equip_type = spear;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 107; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[wepoType]).def_id = 2;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("鉄のメイス"));
			(soubihin[temp].Stype[wepoType]).material = mateIron;
			// weapon_def_list[temp].equip_type = spear;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 44; // 攻撃力
			continue;
		}
	}


	//防具の定義 タテ
// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。
// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("木の盾"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 5; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("鉄の盾"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 30; // 攻撃力
			continue;
		}
	}


	//防具の定義 カブト	
	// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。	
	// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {
		int locType = kabutoType;
		if (temp == 0) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("木の帽子"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 50; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("鉄のカブト"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 20; // 攻撃力
			continue;
		}
	}


	//防具の定義 ヨロイ
	// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。
	// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("--------"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("皮の服"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 2; // 攻撃力
			continue;
		}

		if (temp == 2) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("木のヨロイ"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 5; // 攻撃力
			continue;
		}


		if (temp == 3) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("鎖かたびら"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 10; // 攻撃力
			continue;
		}
	}



	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			magic_def_list[temp].def_id = temp;
			lstrcpy(magic_def_list[temp].def_name, TEXT("ファイア"));
			magic_def_list[temp].power = 1000;
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			magic_def_list[temp].def_id = temp;
			lstrcpy(magic_def_list[temp].def_name, TEXT("アイス"));
			magic_def_list[temp].power = 100;
			continue; // 計算時間の節約のため
		}

	}




	//所持アイテムの個数などの初期値
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


	//所持の装備品の個数などの初期値
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



	//初期装備の武器

	int equipInitialWeaponId = 1;
	equipWeaponPower = weapon_def_list[equipInitialWeaponId].equipPower;


	// mapの情報
	for (int temp = 0; temp <= 1; temp++) {

		if (temp == 0) {
			// map1 にあるマップ遷移の情報
			MapTrans_def_list[temp].MapTrans_id = 1; // そのマップ中で何番目か？
			MapTrans_def_list[temp].in_Where_Map = 1; // map 何番?
			MapTrans_def_list[temp].to_Where_Map = 2;
			MapTrans_def_list[temp].positionX = 7;
			MapTrans_def_list[temp].positionY = 6;

			MapTrans_def_list[temp].chara_positionX = 2;
			MapTrans_def_list[temp].chara_positionY = 1;
		}

		if (temp == 1) {
			// map2 にあるマップ遷移の情報
			MapTrans_def_list[temp].MapTrans_id = 1;
			MapTrans_def_list[temp].in_Where_Map = 2; // map 何番?
			MapTrans_def_list[temp].to_Where_Map = 1;
			MapTrans_def_list[temp].positionX = 2;
			MapTrans_def_list[temp].positionY = 0;

			MapTrans_def_list[temp].chara_positionX = 7;
			MapTrans_def_list[temp].chara_positionY = 4;
		}
	}


	// [30]は文字数であることに注意
	TCHAR TekiList[5][5][30] = {
		{TEXT("1"),TEXT("スライム"), },
		{TEXT("2"),TEXT("コボルト"),}
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




	// モンスターの定義	
	for (int temp = 0; temp <= 1; temp++) {


		lstrcpy(monster_def_list[temp].monster_name, TekiList[temp][1]);

		monster_def_list[temp].monster_id = TekiParam1[temp][0];
		monster_def_list[temp].mon_hp_max = TekiParam1[temp][2];

		monster_def_list[temp].mon_attackPower = TekiParam2[temp][1];
		monster_def_list[temp].mon_agility = TekiParam2[temp][2];

		monster_def_list[temp].mon_exp = TekiParam3[temp][1];
		monster_def_list[temp].mon_gold = TekiParam3[temp][2];

	}

	// 試験的にデータベースの将来実装に向けて配列テスト
	// const化しない。現状では定数だが、将来のデータベース読み込み時に可変として使うので
	//                 =  {id, LV,HP,HPM, agi};
	int NakamaParam1[8][10] = { { 0,1,132,140,56, },
							{ 1,1,108,150,100,}

	};

	// 経験値とか
	//                       id,exp
	int NakamaParam2[8][10] = { { 0,0,0,0, },
							{ 1,0,0,0,}

	};

	// 状態ステータスのフラグ
	//                       id,death,
	int NakamaJotai[8][10] = { { 0,0,0,0, },
							{ 1,0,0,0,}

	};



	// 想定では、本番ではCSVファイルを組み込んで、それを読み込んで配列に代入するスタイルを想定。
	// 現時点では開発段階なので、CSVは未作成。エクセル使うの面倒だし。

	// TCHAR tesqqq[30] = TEXT("aaaa"); // 勉強用 // TCHARの最後の[ ]は文字数だと忘れるな。

	// [30]は文字数であることに注意
	TCHAR NakamaList[5][5][30] = {
		{TEXT("0"),TEXT("エロス"), },
		{TEXT("1"),TEXT("ピエール"),}
	};



	// 装備のフラグ
	//                       id,wep,tate,kabu,
	int NakamaEquipList[8][10] = { { 0, 1,   1,  0, },
							{ 1, 2,   0,  0,}

	};


	// 装備カーソルの位置。このゲームには、これがあるんだった
	//                       id,wep,tate,kabu,
	int NakamaKasolEquip[8][10] = { { 0, 0,   0,  0, },
							{ 1, 0,   0,  0,}

	};



	// パーティ加入フラグ
	// 応急処置
	int PartyInFlag[8][10] = { { 0, 1,   0,  0, },
							{ 1, 1,   0,  0,}

	};


	// キャラクターの定義
	for (int temp = 0; temp <= makeNakamaNinzu + 1; temp++) {

		// キャラ0とキャラ1の初期値代入モジュールの結合テスト
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
			lstrcpy(heros_def_list[temp].heros_name, TEXT("ゴンザレス"));
			heros_def_list[temp].heros_hp = 5; // 55;
			heros_def_list[temp].heros_hp_max = 55;
			heros_def_list[temp].heros_agility = 55;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;

			heros_def_list[temp].heros_shield = 1;
		}

		if (temp == 3) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("ペドロ"));
			heros_def_list[temp].heros_hp = 10;// 12;
			heros_def_list[temp].heros_hp_max = 34;
			heros_def_list[temp].heros_agility = 23;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;

			heros_def_list[temp].heros_shield = 0;
		}


		if (temp == 4) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("テスト用キャラ"));
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
	partyNarabijyun[2] = -1; // マイナス番なら、そこで終了

	// ニューゲームの時点で、戦闘不能フラグを更新
	for (int temp = 0; temp < tourokuNakama; ++temp) {

		if (heros_def_list[temp].heros_hp < 1) {
			heros_def_list[temp].heros_hp = 0;

			// 戦闘不能フラグをオン
			heros_def_list[temp].heros_HP0_flag = 1;
		}

		if (heros_def_list[temp].heros_hp >= 1) {
			// 戦闘不能フラグをOFF
			heros_def_list[temp].heros_HP0_flag = 0;
		}
	}


	int tempHairetu[BATTLE_Agility_proc + 1]; // 使わないかも?

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

	static struct treetype treehen[20]; // 構造体配列の宣言

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
			//	maptreelayer[y][x] = 1; // 通行が不可能
			//}
		}
	}



	for (int y = 0; y <= 7; y = y + 1) {
		for (int x = 0; x <= 10; x = x + 1) {

			if (maptreelayer[y][x] == 0) {
				maptukotable[y][x] = 0;
			}

			if (maptreetable[y][x] == 1 || map1table[y][x]) {
				maptukotable[y][x] = 1; // 通行が不可能
			}
		}
	}






	while (1) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
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

		// バグ防止 キー入力可能なら待機の必要ないので
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



		// マップ描画

		static int mapChipWidthX = 32;
		static int mapChipWidthY = 32;


		static int charaChipWidthX = 32; // 直後ifの外でも使うのでブロック外で定義。
		static int charaChipWidthY = 32;

		static double baiX = waitTime1 / charaChipWidthX; static double baiY = waitTime1 / charaChipWidthY;

		static int tempK = 1;






		// マップ中にあるモンスターシンボルやら町やらのマス位置をあらわす構造体
		// マップイベント用に使いたい
		struct Posi_def
		{
			int PosiX;
			int PosiY;

			// int tempHandle; // すでにグローバル変数で同様の数を定義ずみ
		};

		static struct Posi_def* tempEvAdr;


		// 町は背景に準じるので、モンスターより先に描画。しかしマップイベントであるので、背景とは区別の必要あり。
		// マップイベントのタウン用

		static struct Posi_def town[15];

		tempHandle = townchipDownHandle;


		for (int temp = 0; temp <= 0; temp = temp + 1) {

			// 町座標
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

		// マップ側の町のドット
		for (int temp = 0; temp <= tempTourokusuu1 - 1; temp = temp + 1) {

			// 町画像
			localFunc.localDraw(temp);
			//DrawGraph(mapChipWidthX * (*(tempEvAdr+temp)).PosiX, mapChipWidthY * (*(tempEvAdr+temp)).PosiY, tempHandle, false);

		}



		// モンスターの位置情報
		static struct Posi_def monEv[15];


		tempHandle = monchipDownHandle;

		for (int temp = 1; temp <= 2; temp = temp + 1) {
			//if (enemy_alive[mapEneNum] == 1) {

			monEv[temp - 1].PosiX = monPosiX[temp - 1];
			monEv[temp - 1].PosiY = monPosiY[temp - 1];

		}


		tempEvAdr = monEv;

		// マップ側のモンスターのドット
		// tempTouroku はモンスター登録数
		tempTourokusuu1 = 2;

		for (int temp = 0; temp <= tempTourokusuu1 - 1; temp = temp + 1) {
			//if (enemy_alive[mapEneNum] == 1) {

				// 逃亡用の復活 猶予カウンターをモンスター生存フラグとして流用してるので、下記になる
			if (toubouTyokugo[temp] == 0) {
				// モンスター画像
				localFunc.localDraw(temp);

			}

			if (toubouTyokugo[temp] > 0 && enemy_alive[temp] == 1) {
				// モンスター画像

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
							// モンスター画像
							localFunc.localDraw(temp);

						}

						if (toubouTyokugo[temp] > 0 && enemy_alive[temp] == 1) {
							// モンスター画像

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

		//	__inline void inDraw() { // エラー
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


					// 移動してない下向きは残さないと表示が消える
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




				// 下に移動中のとき、これないと下半身が消える

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



		} // for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw) // yのほう













		// キャラチップ描画
		{

			if (toubouTyokugo[(encount_monsters_id)-1] > 0 && enemy_alive[(encount_monsters_id)-1] == 1 && xPosi == monPosiX[1 - 1] && yPosi == monPosiY[1 - 1]) {

				// 逃亡時に重なってもモンスター表示しないようにする処理
				// DrawGraph(charaChipWidthX * monPosiX[(encount_monsters_id)-1], charaChipWidthY * monPosiY[(encount_monsters_id)-1], blackchipHandle, false);

			}



			// 個別の向きの画像で上書き



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
				// 移動キーのフラグ処理
				{
					int mapsizeX = 10; int mapsizeY = 7;





					{ // 移動のモジュール






						enum nextDirect { up, down, right, left, non };
						enum nextDirect nextDirect_var = non;
						int nextDirFlag = 0;

						if(CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1 && moving == 1 && nextDirFlag == 0 && nyuuryokuMatiLR <5) {
							nextDirect_var = right;
						
						}




						// キャラを右に移動
						if (xPosi < mapsizeX && yPosi < mapsizeY + 1) { // y判定 が+1 してるのはデバッグ用
							// 移動先予定地の入場可否の判定

							if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1 && moving == 0) {
								hero1_direction = rightward;

								if (maptukotable[yPosi][xPosi + 1] == 1) { destMovable = 0; }
								if (maptukotable[yPosi][xPosi + 1] == 0) { destMovable = 1; }

								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi == monPosiY[temp - 1] && xPosi + 1 == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive などで使う


										int taiou[10] = { 2,1,0,0,0,0 }; // エンカウント0番目は敵id2(コボルト)が出現、の意味

										encount_monsters_id = taiou[temp - 1]; // ブロック固有の要素
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}


								//if (yPosi == treehen[0].posiY && xPosi + 1 == treehen[0].posiX ) { destMovable = 0; }

								// 入場可能ならフラグ設定
								if (destMovable == 1) {
									moving = 1;

									keyEnableRight = 0;
									nyuuryokuMatiLR = waitTime1;
								}
							}
							// カウント処理
							if (moving == 1 && nyuuryokuMatiLR > 0) {
								nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
							}
							// 移動の終了処理
							if (hero1_direction == rightward && moving == 1 && nyuuryokuMatiLR <= 0) {
								keyEnableRight = 1; // moving 回復までに時間が掛かるので、ここは1に。

								nyuuryokuMatiLR = waitTime1  ;
								nyuuryokuMatiLeft = waitTime1  ;
								nyuuryokuMatiRight = waitTime1  ;


								xPosi++;     // 右へ1マスだけ移動
								moving = 0;

								townFlag = 0;
							}
						} // 右移動

						// 左に移動
						if (xPosi < mapsizeX + 1 && yPosi < mapsizeY + 1) {      // y判定 が+1 してるのはデバッグ用
							// 移動先予定地の入場可否の判定
							if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1 && moving == 0) {
								hero1_direction = leftward;

								if (maptukotable[yPosi][xPosi - 1] == 1) { destMovable = 0; }
								if (maptukotable[yPosi][xPosi - 1] == 0) { destMovable = 1; }

								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi == monPosiY[temp - 1] && xPosi - 1 == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive などで使う


										int taiou[10] = { 2,1,0,0,0,0 }; // エンカウント0番目は敵id2(コボルト)が出現、の意味

										encount_monsters_id = taiou[temp - 1]; // ブロック固有の要素
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}


								//if (yPosi == treehen[0].posiY && xPosi - 1 == treehen[0].posiX) { destMovable = 0; }

								// 入場可能ならフラグ設定
								if (destMovable == 1) {
									moving = 1;

									keyEnableLeft = 0;
									nyuuryokuMatiLR = waitTime1;
								}
							}
							// カウント処理
							if (moving == 1 && nyuuryokuMatiLR > 0) {
								nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
							}
							// 移動の終了処理
							if (hero1_direction == leftward && moving == 1 && nyuuryokuMatiLR <= 0) {
								keyEnableLeft = 1;

								nyuuryokuMatiLR = waitTime1;
								nyuuryokuMatiLeft = waitTime1;
								nyuuryokuMatiRight = waitTime1;

								xPosi--;    // 左へ1マスだけ移動
								moving = 0;

								townFlag = 0;
							}
						}// 左に移動

						// 下に移動
						if (xPosi < mapsizeX && yPosi < mapsizeY) {
							// 移動先予定地の入場可否の判定
							if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1 && moving == 0) {
								hero1_direction = downward;

								if (maptukotable[yPosi + 1][xPosi] == 1) { destMovable = 0; }
								if (maptukotable[yPosi + 1][xPosi] == 0) { destMovable = 1; }

								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi + 1 == monPosiY[temp - 1] && xPosi == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive などで使う


										int taiou[10] = { 2,1,0,0,0,0 }; // エンカウント0番目は敵id2(コボルト)が出現、の意味

										encount_monsters_id = taiou[temp - 1]; // ブロック固有の要素
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}



								//if (yPosi +1 == treehen[0].posiY && xPosi == treehen[0].posiX) { destMovable = 0; }

								// 入場可能ならフラグ設定
								if (destMovable == 1) {
									moving = 1;

									keyEnableDown = 0;


									nyuuryokuMatiUD = waitTime1;
									nyuuryokuMatiUp = waitTime1;
									nyuuryokuMatiDown = waitTime1;

								}
							}

							// カウント処理
							// keyEnableは別のブロックで流用してるので、必ず moving ==1 が必要
							if (nyuuryokuMatiUD > 0 && moving == 1) {
								nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
							}
							// 移動の終了処理
							if (hero1_direction == downward && nyuuryokuMatiUD <= 0 && moving == 1) {
								keyEnableDown = 1;

								nyuuryokuMatiUD = waitTime1;
								nyuuryokuMatiUp = waitTime1;
								nyuuryokuMatiDown = waitTime1;

								yPosi++;     // 下へ1マスだけ移動
								moving = 0;

								townFlag = 0;
							}
						}// 下に移動


						// 上に移動
						if (xPosi < mapsizeX && yPosi < mapsizeY + 1) {
							// 移動先予定地の入場可否の判定
							if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && moving == 0) {
								hero1_direction = upward;

								if (maptukotable[yPosi - 1][xPosi] == 1) { destMovable = 0; }
								if (maptukotable[yPosi - 1][xPosi] == 0) { destMovable = 1; }

								//int temp = 1;
								for (int temp = 1; temp <= 2; temp = temp + 1) {
									if (yPosi - 1 == monPosiY[temp - 1] && xPosi == monPosiX[temp - 1]
										&& toubouTyokugo[temp - 1] == 0 && enemy_alive[temp - 1] == 1) {

										destMovable = 0;

										mapEneNum = temp; //  2;// enemy_alive などで使う


										int taiou[10] = { 2,1,0,0,0,0 }; // エンカウント0番目は敵id2(コボルト)が出現、の意味

										encount_monsters_id = taiou[temp - 1]; // ブロック固有の要素
										DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


										battle_start();
									}

								}



								//if (yPosi - 1 == treehen[0].posiY && xPosi == treehen[0].posiX) { destMovable = 0; }


								// 入場可能ならフラグ設定
								if (destMovable == 1) {
									moving = 1;

									keyEnableUp = 0;

									nyuuryokuMatiUD = waitTime1;
									nyuuryokuMatiUp = waitTime1;
									nyuuryokuMatiDown = waitTime1;

								}
							}
							// カウント処理

							// keyEnableは別のブロックで流用してるので、必ず moving ==1 が必要
							if (nyuuryokuMatiUD > 0 && moving == 1) {
								nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
							}
							// 移動の終了処理
							if (hero1_direction == upward && nyuuryokuMatiUD <= 0 && moving == 1) {
								keyEnableUp = 1;

								nyuuryokuMatiUD = waitTime1;
								nyuuryokuMatiUp = waitTime1;
								nyuuryokuMatiDown = waitTime1;

								yPosi--;     // 上へ1マスだけ移動
								moving = 0;

								townFlag = 0;
							}
						}// 上に移動
					}// 移動

					// 敵復活カウンター
					// 逃亡処理のフラグ設定っぽい
					// たぶん、歩くたびに逃亡処理判定用のカウンターが+1する

					for (int temp = 1; temp <= 2; temp = temp + 1) {
						if (destMovable == 1 && moving == 1 && toubouTyokugo[temp - 1] > 0) {
							toubouTyokugo[temp - 1] = toubouTyokugo[temp - 1] - 1;
							destMovable = 0;

							// townFlag = 0; // 町から出た処理をついでに。 // 反応しない
						}
						if (toubouTyokugo[temp - 1] <= 0) {
							// toubouSeikou = 0; // これないと再戦時に逃亡成功メッセージが出てしまう // これだとマップ中に一匹でも戦闘可能モンスターがいると0セットになる
							toubouTyokugo[temp - 1] = 0;

							enemy_alive[temp - 1] = 1; // 敵が倒されてた場合は復活するように
						}
					}

					// モンスター遭遇のエンカウント判定
					{
						int monMesX = 400; int monMesY = 350; // メッセージ欄の表示位置


						int taiou[10] = { 2,1,0,0,0,0 }; // エンカウント0番目は敵id2(コボルト)が出現、の意味

						for (int temp = 1; temp <= 2; temp = temp + 1) {
							if (xPosi == monPosiX[temp - 1] && yPosi == monPosiY[temp - 1] && toubouTyokugo[temp - 1] == 0) {

								// モンスター画像 // デバッグ用
								{
									mapEneNum = temp; //  2;// enemy_alive などで使う

									encount_monsters_id = taiou[temp - 1]; // ブロック固有の要素
									DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);


								}


								battle_start();
								// mode_scene = MODE_BATTLE_COMMAND;

								DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
									GetColor(1, 1, 1), 1); // こいつは黒背景
								// window1Draw();
								DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "モンスターが現れた"); // 文字を描画する




							}
						}
						if (!(xPosi == monPosiX[1 - 1] && yPosi == monPosiY[1 - 1])) {
							DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
								GetColor(1, 1, 1), 1); // こいつは黒背景
							// DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "テスト用メッセージ"); // 文字を描画する

						}

					} // モンスター遭遇処理




					// 町に入るのエンカウント判定
					{
						static int where_map = 1;
						check_encount_town();

					} // 町に入るのエンカウント判定


				}

				// if 残り待機がゼロで、さらにXボタンが押されたら、then メニュー画面に遷移

				CheckXetcFunc();
				if (CheckXetc) {
					// keyEnableX = 0;
					mode_scene = MODE_MENU;
					endX();

				}

				int infoX = 100; int infoY = 250;
				window1Draw(infoX, infoY, infoX + 150, infoY + 40 + 100);
				DrawFormatString(infoX, infoY, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する

			} // map モードの終わり



			// タウンの処理


			if (mode_scene == MODE_TOWN) {

				// MessageBox(NULL, TEXT("townのテスト中。"), TEXT("キーテスト"), MB_OK);


				filterFlag = 1;

				// Draw_map(hdc);

				//window1Draw(winX1, winY1 + offsetY * j,	winX2, winY2 + offsetY * j);


				//BrushBlue_set(hdc);
				// Rectangle(hdc, 10, 10, 610, 80);

				//BrushPink_set(hdc);
				//	Rectangle(hdc, 10, 100,	300, 200);

				int mes1X = 220; int mes1Y = 140;
				window1Draw(mes1X, mes1Y, mes1X + 300, mes1Y + 30);

				lstrcpy(mojibuf, TEXT("街に入りました。どこへ行きますか?"));
				// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));
				DrawFormatString(mes1X + 10, mes1Y + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する



				static int offsetYtemp1 = 100;
				// SelectObject(hdc, blue_thin_1);

				window1Draw(10, offsetYtemp1, 200, offsetYtemp1 + 300);

				// Rectangle(hdc, 10, offsetYtemp1,offsetYtemp1 + 100, 400);

				int carsoruHigh = 50; // 文字スパンとカーソル高さは同じにすること

				// BrushPink_set(hdc);
				tenmetu(20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1),
					150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1));

				// Rectangle(hdc, 20, offsetYtemp1 + 10 + carsoruHigh * (whomTargetID1), 150 + 30, offsetYtemp1 + 60 + carsoruHigh * (whomTargetID1));



				window1Draw(10, 80, 100, 120);

				static int offsetXtemp1 = 30; // カーソル高さと同じなのは偶然。
				static int yspan1 = carsoruHigh;

				int temp = 0;

				struct localFuncStruct
				{
					void localText(int temp) {
						DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (temp), GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}
				} localFunc;

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("行き先"));
				//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (temp), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);


				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("ギルド"));
				temp = 1;
				//TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (1), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("宿屋"));
				temp = 2;
				// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (2), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("商店"));
				temp = 3;
				// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (3), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);


				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("出る"));
				temp = 4;
				// TextOut(hdc, offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (4), mojibuf, lstrlen(mojibuf));
				localFunc.localText(temp);



				if (whomTargetID1 == 0) {
					lstrcpy(popMsg, TEXT("パーティの編成をできます。"));
				}

				if (whomTargetID1 == 1 && afterShop == 0) {
					lstrcpy(popMsg, TEXT("HPを全回復します。"));
				}

				if (whomTargetID1 == 2 && afterShop == 0) {
					lstrcpy(popMsg, TEXT("装備品や道具の売買を出来ます。"));
				}

				if (whomTargetID1 == 3 && afterShop == 0) {
					lstrcpy(popMsg, TEXT("街の外に出ます。"));
				}


				if (popFlagTown == 1) {

					lstrcpy(mojibuf, TEXT("                                      "));

					mes1Y = 150 + 30;
					window1Draw(mes1X, mes1Y, mes1X + 300, mes1Y + 30);

					lstrcpy(mojibuf, popMsg);
					DrawFormatString(mes1X + 10, mes1Y + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}

				// temp == tourokuNakama + 1    に相当		
				// _stprintf_s(mojibuf, MAX_LENGTH, TEXT("【外す】"));		
				// TextOut(hdc, offsetXtemp1, 30 - 10 + yspan1 * (tourokuNakama + 1) + 120, mojibuf, lstrlen(mojibuf));





				struct localFuncStruct2
				{
					void localExit() {
						townFlag = 1; // タウン退出には、これが必要
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



				// 十字キー入力時

				int rangeMin = 0; int rangeMax = 3;

				// カーソルを上に移動
				{
					// 移動の終了処理
					CheckUPetcFunc();
					if (CheckUPetc) {

						endUP();


						selecting_mainmenu--;     // 上へ1マスだけ移動

						afterShop = 0;
					}
				}

				// カーソルを下に移動
				{
					// 移動の終了処理
					CheckDOWNetcFunc();
					if (CheckDOWNetc) {

						endDOWN();

						selecting_mainmenu++;      // 下へ1マスだけ移動

						afterShop = 0;
					}
				}

				// 共通の後処理
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


					// 宿
					if (whomTargetID1 == 1) {

						popFlagTown = 1;
						afterShop = 1;
						lstrcpy(popMsg, TEXT("全回復した。"));

						int tempYado; // for で使う
						// partyNinzuDone


						int aaaa = 0;

						for (aaaa = 0; aaaa <= partyNinzuDone - 1; aaaa = aaaa + 1) {

							tempYado = partyNarabijyun[aaaa];
							heros_def_list[tempYado].heros_hp = heros_def_list[tempYado].heros_hp_max;
							// heros_def_list[tempYado].heros_mp = heros_def_list[tempYado].heros_mp_max;

						}
					} // 宿


					// 商店
					if (whomTargetID1 == 2) {

						// MessageBox(NULL, TEXT("未実装。"), TEXT("キーテスト"), MB_OK);

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

				// MessageBox(NULL, TEXT("ギルドのテスト中。"), TEXT("キーテスト"), MB_OK);

				// BrushBlue_set(hdc);
				// Rectangle(hdc, 10, 10, 610, 80);

				// BrushPink_set(hdc);
				//	Rectangle(hdc, 10, 100,	300, 200);


				filterFlag = 1;

				hikaesai();
				parsai();



				lstrcpy(mojibuf, TEXT("誰を仲間にしますか？ 選んでください。"));
				// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));
				DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				lstrcpy(mojibuf, TEXT("Xボタンで退出。          "));
				// TextOut(hdc, 280, 350, mojibuf, lstrlen(mojibuf));
				DrawFormatString(280, 350, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				if (partyNinzuTemp <= 0) {

					lstrcpy(mojibuf, TEXT("パーティ人数が1人以上必要です。"));
					//TextOut(hdc, 280, 350, mojibuf, lstrlen(mojibuf));

					DrawFormatString(280, 350, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}




				_stprintf_s(
					mojibuf, MAX_LENGTH, TEXT("%d"),
					partyNinzuDone);
				// TextOut(hdc, 280, 310, mojibuf, lstrlen(mojibuf));
				DrawFormatString(280, 310, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				CheckXetcFunc();
				if (CheckXetc) {
					//MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);

					partyNinzuDone = partyNinzuTemp;
					mode_scene = MODE_TOWN;

					endX();
				}

				CheckZetcFunc();
				if (CheckZetc && whomCHARA == hikaeNinzu + 1) {
					//MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);

					// keyHaijyo = 1;

					whomCHARA = hikaeNinzu; // また「外す」にあってるのは面倒なので 1つ下げる。

					partyNinzuDone = partyNinzuTemp;

					whomCHARA = 0;
					mode_scene = MODE_Guild_Remove;

					endZ();
				}


				CheckZetcFunc();
				if (CheckZetc && whomCHARA != hikaeNinzu + 1) {


					if (uwadumeFlag == 0) {

						if (akikosuu >= 1 && whomCHARA - 1 <= tourokuNakama) {  // パーティ側の空き個数
						// こっちはパーティ側の上書き用
							if (heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn == 0) {

								heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn = 1;

								// 仕様変更により、順番を変えてもバグらない。
								// 下記の順序を守ること・・・だった。守らないとバグだった。
								partyNarabijyun[akiHairetu[0]] = whomCHARA - 1; // 先に代入
								// 人数の更新
								partyNinzuTemp = partyNinzuTemp + 1; // あとから人数を加算
								hikaeNinzu = hikaeNinzu - 1;

								akiHairetu[0] = akiHairetu[1];

								uwagaki = 1;

								akikosuu = akikosuu - 1;


								endZ();

								mode_scene = MODE_Guild_Responce; // レスポンス中に空き配列の計算をするので残すこと


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

						// パーティ加入すると控え人数が変わるので、移動先モード判定は先に行う必要あり。
						if (whomCHARA == hikaeNinzu + 1) {

							uwagaki = 1;

							mode_scene = MODE_Guild_Remove;






							break; // 下記の加入モードをbreakで省略しないと行けないので、ここにbreak
						}


						// 以下、メインモード。

						if (akikosuu >= 1 && whomCHARA - 1 <= tourokuNakama) {  // パーティ側の空き個数



						// こっちはパーティ側の上書き用
							if (heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn == 0) {


								// MessageBox(NULL, TEXT("押され33。"), TEXT("キーテスト"), MB_OK);


								heros_def_list[hikaeNarabijyun[whomCHARA - 1]].PartyIn = 1;

								// 仕様変更により、順番を変えてもバグらない。
								// 下記の順序を守ること・・・だった。守らないとバグだった。
								partyNarabijyun[akiHairetu[0]] = hikaeNarabijyun[whomCHARA - 1]; // 先に代入
								// 人数の更新
								partyNinzuTemp = partyNinzuTemp + 1; // あとから人数を加算


								hikaeNinzu = hikaeNinzu - 1;



								akiHairetu[0] = akiHairetu[1];

								uwagaki = 1;

								akikosuu = akikosuu - 1;

								mode_scene = MODE_Guild_Responce; // レスポンス中に空き配列の計算をするので残すこと

							}
						}


						if (akikosuu <= 0) {
							// MessageBox(NULL, TEXT("押され。"), TEXT("キーテスト"), MB_OK);

							mode_scene = MODE_Guild_Main;


						}


						// ギルド突入時にも処理しているが、突入処理はここでは不要なので、こっちでも別途、実装。
						// 控えメンバー側のリスト描画
						hikaeKeisan();

					}


				}




				if (mode_scene == MODE_Guild_Main) { // remove時に共通動作を封じるため


					CheckUPetcFunc();
					if (CheckUPetc) {
						// MessageBox(NULL, TEXT("上が押されました。"), TEXT("キーテスト"), MB_OK);
						whomCHARA = whomCHARA - 1;

						if (whomCHARA > hikaeNinzu) {
							whomCHARA = hikaeNinzu;
						}


						endUP();
					}


					CheckDOWNetcFunc();
					if (CheckDOWNetc) {



						// MessageBox(NULL, TEXT("↓が押されました。"), TEXT("キーテスト"), MB_OK);

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
					//MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);

					keyEnableZ = 0;
					partyNinzuTemp = partyNinzuTemp - 1;

					heros_def_list[partyNarabijyun[whomTargetID1party]].PartyIn = 0; // 先に控えをコピーしてから（次行）
					partyNarabijyun[whomTargetID1party] = -1; // パーティ側をカラにする。


					akikosuu = akikosuu + 1;


					Akihaikeisan();


					hikaeNinzu = hikaeNinzu + 1;

					// これが加わる
					hikaeKeisan();








					if (partyNinzuTemp >= 1) {



						int skip = 0;
						int kousinNarabijyun[partymax];

						partyNinzuDone = partyNinzuTemp;
						// MessageBox(NULL, TEXT("xxxxxxxが押されました。"), TEXT("キーテスト"), MB_OK);




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
					//MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);

					partyNinzuDone = partyNinzuTemp;
					mode_scene = MODE_Guild_Main;

					endX();
				}


				CheckUPetcFunc();
				CheckDOWNetcFunc();


				if (CheckUPetc || CheckDOWNetc) {

					if (CheckUPetc) {
						// MessageBox(NULL, TEXT("上が押されました。"), TEXT("キーテスト"), MB_OK);
						whomCHARA = whomCHARA - 1;

						if (whomCHARA > partyNinzuTemp) {
							whomCHARA = partyNinzuTemp;
						}


						endUP();
					}


					if (CheckDOWNetc) {

						endDOWN();

						// MessageBox(NULL, TEXT("↓が押されました。"), TEXT("キーテスト"), MB_OK);

						whomCHARA = whomCHARA + 1;

						if (whomCHARA > partyNinzuTemp + 1) {
							whomCHARA = partyNinzuTemp + 1;
						}

					}

					// 共通処理
					if (whomCHARA < 1) {
						whomCHARA = 1;
					}
					whomTargetID1 = whomCHARA - 1;

					beforeselect = whomCHARA;

					whomTargetID1party = whomTargetID1;



				} // if ((CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1)


			}


			if (mode_scene == MODE_Guild_Responce) {

				// MessageBox(NULL, TEXT("ギルドのテスト中。"), TEXT("キーテスト"), MB_OK);

				//BrushBlue_set(hdc);
				//BrushPink_set(hdc);

				lstrcpy(mojibuf, TEXT("誰を仲間にしますか？ 選んでください。"));
				// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));
				DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				hikaesai();
				parsai();


				// ここが上書きされている。
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s が仲間に加わった。"), heros_def_list[whomTargetID1hikae].heros_name);
				// TextOut(hdc, 280, 300, mojibuf, lstrlen(mojibuf));
				DrawFormatString(280, 300, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				lstrcpy(mojibuf, TEXT("Xボタンで退出。"));
				// TextOut(hdc, 280, 350, mojibuf, lstrlen(mojibuf));

				DrawFormatString(280, 350, GetColor(255, 255, 255), mojibuf); // 文字を描画する


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


				// 「売る」のあとに「買う」したときの表示文の残骸の一旦クリア用
				for (int temp = 0; temp <= 6; temp = temp + 1) {
					lstrcpy(mojibuf, TEXT("   "));
					//TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
					//DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}


				int koumoku_Y = 200;
				int kasolOffsetY = 30;



				//shopCommand();

				shopHinBack();
				shopKoumoku();

				hinmokuView();









				lstrcpy(mojibuf, TEXT("商店に入りました。どこへ行きますか?"));
				//TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

				int XXX = 150; int YYY = 50;
				window1Draw(XXX - 10, YYY - 10, XXX + 300, YYY + 30);
				DrawFormatString(XXX, YYY, GetColor(255, 255, 255), mojibuf); // 文字を描画する





				if (popFlagTown == 1) {

					lstrcpy(mojibuf, TEXT("                                      "));
					// TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));

					//DrawFormatString(130, 150, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					lstrcpy(mojibuf, popMsg);
					//TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));


				}

				tempPass = whomTargetID1;






				// 十字キー入力時
				int rangeMin = 0; int rangeMax = 4;

				// カーソルを上に移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
						keyEnableUp = 0;
						nyuuryokuMatiUp = waitTime1;
						selecting_mainmenu--;     // 上へ1マスだけ移動

					}


					if (selecting_mainmenu < rangeMin) {
						selecting_mainmenu = rangeMin;
					}

					if (selecting_mainmenu >= rangeMax) {
						selecting_mainmenu = rangeMax;
					}
				}

				// カーソルを下に移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
						keyEnableDown = 0;
						nyuuryokuMatiDown = waitTime1;
						selecting_mainmenu++;                       // 下へ1マスだけ移動
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

					} // 宿


					// sousyoku
					if (whomTargetID1 == 2) {
						shopMijissou = 1;

						endZ();
						MessageBox(NULL, TEXT("未実装。"), TEXT("キーテスト"), MB_OK);

					}

					// dougu
					if (whomTargetID1 == 3) {
						shopMijissou = 1;

						endZ();
						MessageBox(NULL, TEXT("未実装。"), TEXT("キーテスト"), MB_OK);

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

				// MessageBox(NULL, TEXT("ギルドのテスト中。"), TEXT("キーテスト"), MB_OK);


				{
					//BrushDarkBlue_set(hdc);
					// Rectangle(hdc, 10, 10, 610, 80);

					// BrushDarkPink_set(hdc);
					//	Rectangle(hdc, 10, 100,	300, 200);


					lstrcpy(mojibuf, TEXT("商店に入りました。どこへ行きますか?"));
					// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

					//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					shopCommon1();

					int offsetXtemp1 = 30; // カーソル高さと同じなのは偶然。
					int carsoruHigh = 30;
					int yspan1 = carsoruHigh;

					//DrawFormatString(offsetXtemp1, -10 + offsetYtemp1 + yspan1 * (5), GetColor(255, 255, 255), mojibuf); // 文字を描画する



					// 十字キー入力時
					int rangeMin = 0; int rangeMax = 3;







				}



				if (popFlagTown == 1) {

					lstrcpy(mojibuf, TEXT("                                      "));
					// TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));

					DrawFormatString(130, 150, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					lstrcpy(mojibuf, popMsg);
					//TextOut(hdc, 130, 150, mojibuf, lstrlen(mojibuf));


				}



				//BrushBlue_set(hdc);
				//BrushPink_set(hdc);

				if (mode_scene == MODE_Shop_weapon_main) {
					//lstrcpy(mojibuf, TEXT("武器屋テスト。"));
				}
				if (mode_scene == MODE_Shop_armor_main) {
					//lstrcpy(mojibuf, TEXT("防具屋テスト。"));
				}
				//TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

				//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

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

				// デバッグ用
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), buyrange);
				DrawFormatString(280 + 100 * 3 + 50, koumoku_Y + 30 + kasolOffsetY * 5, GetColor(255, 255, 255), mojibuf); // 文字を描画する




				// 十字キー入力時
				int rangeMin = 0; int rangeMax = 4;


				// カーソルをmigiに移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
						keyEnableLeft = 0;
						nyuuryokuMatiLeft = waitTime1;
						whomTargetID2--;     // 上へ1マスだけ移動

					}


					if (whomTargetID2 < rangeMin) {
						whomTargetID2 = rangeMin;
					}

					if (whomTargetID2 >= rangeMax) {
						whomTargetID2 = rangeMax;
					}
				}

				// カーソルをhidariに移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {
						keyEnableRight = 0;
						nyuuryokuMatiRight = waitTime1;
						whomTargetID2++;                       // 下へ1マスだけ移動
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


					//MessageBox(NULL, TEXT("デバッグ。"), TEXT("テスト"), MB_OK);



					// カーソルをueに移動
						{

							// 移動の終了処理
							if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
								keyEnableUp = 0;
								nyuuryokuMatiUp = waitTime1;



								whomTargetID1--;     // 上へ1マスだけ移動

							}


							if (whomTargetID1 < rangeMin) {
								whomTargetID1 = rangeMin;
							}

							if (whomTargetID1 >= rangeMax) {
								whomTargetID1 = rangeMax;
							}
						}

						// カーソルをsitaに移動
						{

							// 移動の終了処理
							if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
								keyEnableDown = 0;
								nyuuryokuMatiDown = waitTime1;
								whomTargetID1++;                       // 下へ1マスだけ移動
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


					// 商店
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
						//	townFlag = 1; // タウン退出には、これが必要
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


					lstrcpy(mojibuf, TEXT("商店に入りました。どこへ行きますか?"));
					// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));


					//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する



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


				// 「売る」のあとに「買う」したときの表示文の残骸の一旦クリア用
				for (int temp = 0; temp <= 6; temp = temp + 1) {
					lstrcpy(mojibuf, TEXT("   "));
					//TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
					DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する



				}


				hinmokuView();




				int koumoku_Y = 200;
				int kasolOffsetY = 30;




				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), buyrange);
				DrawFormatString(280 + 100 * 3 + 50, koumoku_Y + 30 + kasolOffsetY * 5, GetColor(255, 255, 255), mojibuf); // 文字を描画する



				CheckZetcFunc();
				if (CheckZetc) {

					int locType2 = itemTypeHairetu[whomTargetID4];
					// 買う処理
					if (your_money >= 50) {

						(soubiSyoji[itemHairetu[whomTargetID4]].Stype[locType2]).have_kosuu =
							(soubiSyoji[itemHairetu[whomTargetID4]].Stype[locType2]).have_kosuu + 1;

						// weapon_have_list[itemHairetu[whomTargetID1]].have_kosuu = weapon_have_list[itemHairetu[whomTargetID1]].have_kosuu + 1;
						your_money = your_money - 50;

					}
					// 売る処理
					// 売り物なし


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


					lstrcpy(mojibuf, TEXT("商店に入りました。どこへ行きますか?"));
					// TextOut(hdc, 130, 50, mojibuf, lstrlen(mojibuf));

					//DrawFormatString(130, 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					shopCommon1();

					// 十字キー入力時
					int rangeMin = 0; int rangeMax = 3;
				}





				shopCommand();

				shopHinBack();

				////////////// 何かのコピペの境


				int spanY = 30;
				int Y0 = 120;


				int itemskip = 0;
				goukeiItem = 0;

				int itemIDcount = 0;
				int column = 1; // 1に変更

				int xcommon;
				int ycommon;


				// アイテム処理用
				itemskip = 0;
				int LimintTemp = goukeiItem;


				// 使用品の配列代入
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
				} // 使用品の配列代入



				itemskip = 0;
				LimintTemp = goukeiItem;

				//int locType2;

				// 武器の配列代入
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
				} // 武器の配列代入



				itemskip = 0;
				LimintTemp = goukeiItem;

				// シールドの配列代入
				for (idTemp = 1; idTemp <= 2; idTemp = idTemp + 1)
				{
					if ((soubiSyoji[idTemp].Stype[tateType]).have_kosuu != 0) {
						// MessageBox(NULL, TEXT("テストhelm"), TEXT("キーテスト"), MB_OK);

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
				} // シールド

				itemskip = 0;
				LimintTemp = goukeiItem;
				// ヘルムの配列代入
				for (idTemp = 1; idTemp <= 2; idTemp = idTemp + 1)
				{
					// MessageBox(NULL, TEXT("テスト22"), TEXT("キーテスト"), MB_OK);
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
				} // かぶとの配列代入

				itemTypeHairetu[itemIDcount] = -99; // 終了を意味する数。


				//BrushPink_set(hdc);
				tenmetu(280, 200 + 60 + 30 * (whomTargetID4),
					320 + 40, offsetYtemp1 + 60 + 60 + 30 * (whomTargetID4));

				//SetBkColor(hdc, RGB(0xFF, 0xFF, 0xFF));
				//SetBkMode(hdc, OPAQUE);

				// 見出し
				shopKoumoku();


				// ページ送り時の一旦クリア用
				for (int temp = 0; temp <= 6; temp = temp + 1) {
					lstrcpy(mojibuf, TEXT("   "));
					// TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

					DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する



				}

				if (1) {
					for (int temp = 0; temp <= 10; temp = temp + 1) {


						int temp2 = temp + pageSyori * 6;

						if (itemTypeHairetu[temp2] == -99) {
							lstrcpy(mojibuf, TEXT("   "));
							//TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

							DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する


							break;
						}

						int locType2 = itemTypeHairetu[temp2]; // itemHairetu ではない。 Type なし


						if (itemTypeHairetu[temp2] == siyouType) {
							// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

							lstrcpy(mojibuf, item_def_list[itemHairetu[temp2]].def_name);
						}

						// else をつけないと、なぜかsiyouhin 情報を壊す
						else if (itemTypeHairetu[temp2] == wepoType || tateType || kabutoType) {
							lstrcpy(mojibuf, (soubihin[itemHairetu[temp2]].Stype[locType2]).def_name);
						}


						// TextOut(hdc, 280, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
						DrawFormatString(280, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する


						lstrcpy(mojibuf, TEXT("50G"));
						// TextOut(hdc, 280 + 120, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

						DrawFormatString(280 + 120, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する



						// 個数欄の背景クリア用
						lstrcpy(mojibuf, TEXT("   "));
						// TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));

						DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する



						if (itemTypeHairetu[temp2] == siyouType) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), item_have_list[itemHairetu[temp2]].have_kosuu);

							//_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), itemTypeHairetu[temp2]);


						}

						// else をつけないと、なぜかsiyouhin 情報を壊す
						else if (itemTypeHairetu[temp2] == wepoType || tateType || kabutoType) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[itemHairetu[temp2]].Stype[locType2]).have_kosuu);

							// _stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), itemTypeHairetu[temp2]);
							// lstrcpy(mojibuf, ( soubiSyoji[itemHairetu[temp2]].Stype[locType2]).have_kosuu);
						}



						// TextOut(hdc, 280 + 100 * 2 + 50, 200 + 30 * (temp + 1), mojibuf, lstrlen(mojibuf));
						DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する

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
						// MessageBox(NULL, TEXT("ページ戻し処理の調査テスト"), TEXT("キーテスト"), MB_OK);
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
					//MessageBox(NULL, TEXT("ページ送り処理の調査テスト"), TEXT("キーテスト"), MB_OK);
					pageSyori = 1;
					whomTargetID4 = 0;
				}

				if (goukeiItem <= 0) {
					// MessageBox(NULL, TEXT("ページ送り処理の調査テスト"), TEXT("キーテスト"), MB_OK);
					whomTargetID4 = 0;
				}







				CheckZetcFunc();
				if (CheckZetc) {


					int temp2 = whomTargetID4 + pageSyori * 6;

					// MessageBox(NULL, TEXT("なかルーチン"), TEXT("キーテスト"), MB_OK);
					// mode_scene = MODE_Shop_Main;

					sinamonoList = 1;
					// 売る処理

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

				int monMesX = 400; int monMesY = 350; // メッセージ欄の表示位置
				DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
					GetColor(1, 1, 1), 1);
				DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "モンスターが現れた"); // 文字を描画する

				// モンスター画像 
				if (mode_scene == MODE_BATTLE_COMMAND || mode_scene == MODE_BATTLE_COMMAND2 || mode_scene == MODE_BATTLE_MAGIC || mode_scene == MODE_BATTLE_NOW) {

					{
						DrawGraph(300, 95, monsHandle[encount_monsters_id - 1], true);
					}


				}


				// 敵関係のパラメ－タ表示
				int monX = 450;
				int monY = 150;

				tekiTairetuAgility[0] = monster_def_list[encount_monsters_id - 1].mon_agility;


				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("HP %d"), monster_hp);
				DrawFormatString(monX, monY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), monster_name);
				DrawFormatString(monX, monY + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("素早さ %d"), tekiTairetuAgility[0]);
				DrawFormatString(monX, monY + 20 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				int windowTempA = 410 + 100; // y の位置
				int chara_window_size_x = 140;

				// _itot_s(your_money , p,200, 10); // 難しい関数なので保管

				int offsetBattleX = 170;
				int tempVAl;


				for (int iTemp = 0; iTemp <= partyNinzuDone - 1; iTemp++)
				{

					window1Draw(10 + iTemp * offsetBattleX, 350,
						10 + iTemp * offsetBattleX + 150, 470);

					tempVAl = partyNarabijyun[iTemp];


					/* キャラのステータス */
					DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 10,
						GetColor(255, 255, 255), heros_def_list[tempVAl].heros_name); // 文字を描画する


					lstrcpy(mojibuf, TEXT("HP"));
					DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[tempVAl].heros_hp);
					DrawFormatString(50 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[tempVAl].heros_hp_max);
					DrawFormatString(50 + 30 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					lstrcpy(mojibuf, TEXT("素早さ"));
					DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), sankaAgility[tempVAl]);
					DrawFormatString(50 + iTemp * offsetBattleX + 30, windowTempA - chara_window_size_x + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}


				for (idTemp = 0; idTemp <= partyNinzuDone - 1; idTemp = idTemp + 1)
				{
					// パーティにいないキャラごと、読み取る。
					// パーティキャラの抽出は、後工程で行う。
					mikataAgility[idTemp] = heros_def_list[idTemp].heros_agility;
				}


				// これ戦闘用ソート
				for (idTemp = 0; idTemp <= partyNinzuDone - 1; idTemp = idTemp + 1)
				{
					// ここでパーティキャラだけ素早さを抽出している。mikataAgi は非パーティキャラを含んでるので、この工程が必要。
					sankaAgility[idTemp] = mikataAgility[partyNarabijyun[idTemp]]; // sankaAgil はまだ並び替え前

				}

				for (idTemp = 0; idTemp <= enemyNinzu - 1; idTemp = idTemp + 1)
				{
					sankaAgility[partyNinzuDone + idTemp] = tekiTairetuAgility[idTemp];

				}


				for (int loctempQ = 0; loctempQ <= partyNinzuDone + enemyNinzu - 1; ++loctempQ)
				{
					iremonoAgilityHairetu[loctempQ] = sankaAgility[loctempQ]; // iremonoAgi と sanka は同内容

					iremonoOrderHairetu[loctempQ] = loctempQ;
				} // 初期値の代入


				// ソートで実装

				for (int loctempB = 0; loctempB <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1; ++loctempB)
				{
					for (int loctempA = loctempB; loctempA <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1; ++loctempA)
					{
						if (iremonoAgilityHairetu[loctempB] >= iremonoAgilityHairetu[loctempA + loctempB]) {

							// 何もしていない
						//	iremonoAgilityHairetu[loctempB] = iremonoAgilityHairetu[loctempB];
						//	iremonoAgilityHairetu[loctempA + loctempB] = iremonoAgilityHairetu[loctempA + loctempB];
							// 教育用に上コード2行は残す

						}
						// locAのほうが内側です。
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

							// デバッグ文の「irem」では入れ物オーダー配列である。
						}
					}
				} // ここまでソート


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


				// 素早さ配列の表示テスト
				int agilityProcMonitorX = 370;
				int agilityProcMonitorY = 180;


				if (debugFlag == 1) {
					lstrcpy(mojibuf, TEXT("素早さ配列"));

					DrawFormatString(agilityProcMonitorX, agilityProcMonitorY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), iremonoAgilityHairetu[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}
					// 戦闘デバッグ文の描画プログラム


					// 行動順配列の表示テスト 
					lstrcpy(mojibuf, TEXT("行動順配列"));
					DrawFormatString(agilityProcMonitorX, agilityProcMonitorY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					lstrcpy(mojibuf, TEXT("irem"));
					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), iremonoOrderHairetu[tempMonitor]);
						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する
					}


					// 行動順配列の表示テスト // こっちはactionOrder
					lstrcpy(mojibuf, TEXT("act"));

					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("v%d"), actionOrder[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する
					}

					lstrcpy(mojibuf, TEXT("PE f"));

					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), PorEflag[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}

					lstrcpy(mojibuf, TEXT("Ac tp"));

					DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), actionOrder[tempMonitor]);

						DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}
				} // ここまでデバッグ文



				if (mode_scene == MODE_BATTLE_COMMAND) {
					int tem1X = 100; int Xwidth = 100;
					int tem1Y = 240;

					int yohakuY = 10;
					window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
						tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

					// カーソル
					tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
						tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);


					int ComdTemp[5]; // のちのターン開始if文で流用するので配列定義

					for (int temp = 0; temp <= 1; temp = temp + 1) {

						ComdTemp[temp] = temp;

						if (ComdTemp[temp] == 0) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦う")); }
						if (ComdTemp[temp] == 1) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("逃げる")); }

						DrawFormatString(tem1X + 20, tem1Y + 10 + 40 * ComdTemp[temp], GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}

					// ターン開始 of 戦うコマンド
					if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == ComdTemp[0] + 1 && keyHaijyo == 0
						// && mode_scene == MODE_BATTLE_COMMAND // これが無いと連打でターン再開してしまう // 上記コマンド一覧と統合のため除去
						) {

						// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

						TimeKasolCount = 10;

						keyHaijyo = 0;
						battlewait = 100;

						dameKei = 0;

						damage_EnemyAttack = 0;
						damage_HeroAttack = 0;

						selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] +1;
						mode_scene = MODE_BATTLE_COMMAND2;
						//mode_scene = MODE_BATTLE_NOW;

					} // ターン開始 of 戦うコマンド



					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 は「windowTempA」

					// デバッグ文
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("nmUP %d"), nyuuryokuMatiUp );
						DrawFormatString(battleMassBaseX + 200 + 80 * 1 , battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("keUP %d"), keyEnableUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 2 , battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("pag並び %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("partyNin %d"), partyNinzuDone); //sentouNaninme
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					} // ここまでデバ文



				} //  MODE_BATTLE_COMMAND




				if (mode_scene == MODE_BATTLE_COMMAND2) {
					int tem1X = 100; int Xwidth = 100;
					int tem1Y = 240;

					int yohakuY = 10;
					window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
						tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

					// カーソル
					tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
						tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);


					int ComdTemp[5]; // のちのターン開始if文で流用するので配列定義

					for (int temp = 0; temp <= 1; temp = temp + 1) {

						ComdTemp[temp] = temp;

						if (ComdTemp[temp] == 0) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("攻撃")); }
						if (ComdTemp[temp] == 1) { _stprintf_s(mojibuf, MAX_LENGTH, TEXT("魔法")); }

						DrawFormatString(tem1X + 20, tem1Y + 10 + 40 * ComdTemp[temp], GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}

					_stprintf_s(mojibuf, TEXT("%s"), heros_def_list[sentouNaninme].heros_name ); //sentouNaninme

					DrawFormatString(tem1X + 100, tem1Y + 30 , GetColor(255, 255, 255), mojibuf); // 文字を描画する



					// ターン開始 of 戦うコマンド
					if (CheckHitKey(KEY_INPUT_Z) == 1 && keyHaijyo == 0 && TimeKasolCount > 20
						) {

						if (selecting_mainmenu == ComdTemp[0] + 1 ) {

							zenkaiBcKasol_1[sentouNaninme] = selecting_mainmenu -1;

							if (sentouNaninme >= partyNinzuDone-1) {
								// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

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
								//MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);


								koudouKiroku[sentouNaninme] = koudouAtk;

								sentouNaninme = sentouNaninme + 1;
								TimeKasolCount = 0;

								
								selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] + 1;

								// selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] ;

							} // ターン開始 of 戦うコマンド							
						}


						else if (selecting_mainmenu == ComdTemp[0] + 2) {

							zenkaiBcKasol_1[sentouNaninme] = selecting_mainmenu -1;

							if (sentouNaninme < partyNinzuDone) {
								//MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);
								//sentouNaninme = sentouNaninme + 1;

								TimeKasolCount = 0;

								selecting_mainmenu = zenkaiBcKasol_2[sentouNaninme] + 1;
								mode_scene = MODE_BATTLE_MAGIC;
								koudouKiroku[sentouNaninme] = koudouMgk;
								magicAtkFlag[sentouNaninme] = 0;
							}

							if (sentouNaninme >= partyNinzuDone) {
								// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

								TimeKasolCount = 0;
							
								selecting_mainmenu = zenkaiBcKasol_2[sentouNaninme] + 1;
								mode_scene = MODE_BATTLE_MAGIC;
								koudouKiroku[sentouNaninme] = koudouMgk;
								magicAtkFlag[sentouNaninme] = 0;

								
							}
							// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);
						} // ターン開始 of 戦うコマンド
					} // z


					// キャンセル
					if (CheckHitKey(KEY_INPUT_X) == 1 && keyHaijyo == 0 && TimeKasolCount > 20
						// && mode_scene == MODE_BATTLE_COMMAND // これが無いと連打でターン再開してしまう // 上記コマンド一覧と統合のため除去
						) {

						if (sentouNaninme == 0) {
							// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

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
							// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

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



					} // キャンセル


					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 は「windowTempA」

					// デバッグ文
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("nmUP %d"), nyuuryokuMatiUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 1, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("keUP %d"), keyEnableUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 2, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("pag並び %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("partyNin %d"), partyNinzuDone);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("sento %d"), sentouNaninme);
						DrawFormatString(battleMassBaseX + 200+150, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("zkB[sN] %d"), zenkaiBcKasol_1[sentouNaninme] );
						DrawFormatString(battleMassBaseX + 200 + 150, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("zkB2[sN] %d"), zenkaiBcKasol_2[sentouNaninme]);
						DrawFormatString(battleMassBaseX + 200 + 150, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する



						// zenkaiBcKasol_1[sentouNaninme]



					} // ここまでデバ文

				} //  MODE_BATTLE_COMMAND2



				if (mode_scene == MODE_BATTLE_MAGIC) {
					int tem1X = 100; int Xwidth = 100;
					int tem1Y = 240;

					int yohakuY = 10;
					window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
						tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

					// カーソル
					tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
						tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);


					int ComdTemp[5]; // のちのターン開始if文で流用するので配列定義

					for (int temp = 0; temp <= 1; temp = temp + 1) {

						// magicList											
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), magic_def_list[temp].def_name);	

						ComdTemp[temp] = temp; // これ消すと表示位置がズレるので残せ
						DrawFormatString(tem1X + 20, tem1Y + 10 + 40 * ComdTemp[temp], GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}


					_stprintf_s(mojibuf, TEXT("%s"), heros_def_list[sentouNaninme].heros_name); //sentouNaninme

					DrawFormatString(tem1X + 100, tem1Y + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					//MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

					// ターン開始 of 戦うコマンド
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

								//MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);
								sentouNaninme = sentouNaninme + 1;
								selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] + 1;

								keyHaijyo = 0;

								TimeKasolCount = 0;
								mode_scene = MODE_BATTLE_COMMAND2;

								
								
							}


							
							 if (sentouNaninme >= partyNinzuDone ) {
								//MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);
								//sentouNaninme = sentouNaninme + 1;

								keyHaijyo = 1;

								TimeKasolCount = 0;
								mode_scene = MODE_BATTLE_NOW;
								magicKiroku[sentouNaninme] = magicSel;
								magicAtkFlag[sentouNaninme] = 1;

								selecting_mainmenu = zenkaiBcKasol_1[sentouNaninme] + 1;
							}


						} // ターン開始 of 戦うコマンド


					}



					// キャンセル
					if (CheckHitKey(KEY_INPUT_X) == 1 && keyHaijyo == 0 && TimeKasolCount > 20	) {

						// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

						TimeKasolCount = 0;

						keyHaijyo = 0;
						battlewait = 100;

						dameKei = 0;

						damage_EnemyAttack = 0;
						damage_HeroAttack = 0;


						mode_scene = MODE_BATTLE_COMMAND2;
						//mode_scene = MODE_BATTLE_NOW;

					} // ターン開始 of 戦うコマンド


					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 は「windowTempA」

					// デバッグ文
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("nmUP %d"), nyuuryokuMatiUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 1, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("keUP %d"), keyEnableUp);
						DrawFormatString(battleMassBaseX + 200 + 80 * 2, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("pag並び %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(mojibuf, TEXT("partyNin %d"), partyNinzuDone);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する




					} // ここまでデバ文

					//MessageBox(NULL, TEXT("test。"), TEXT("magic end 場所テスト"), MB_OK);

				} //  MODE_BATTLE_magic


				// 十字キー入力時
				if (keyHaijyo == 0) {
					// カーソルを上に移動

					{

						// 移動の終了処理
						CheckUPetcFunc();

						// if (CheckUPetc) {
						if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && nyuuryokuMatiUp <= 0) {
							endUP();

							// MessageBox(NULL, TEXT("上キー2テスト。"), TEXT("場所テスト"), MB_OK);


							selecting_mainmenu--;  // 上へ1マスだけ移動
						}

						// 数値が微妙に違うので、リファクタ統合するな
						if (selecting_mainmenu < 0) {
							selecting_mainmenu = 0;
						}

						if (selecting_mainmenu >= 3) {
							selecting_mainmenu = 3;
						}
					}


					// カーソルを下に移動
					{

						// 移動の終了処理
						CheckDOWNetcFunc();
						if (CheckDOWNetc) {
							endDOWN();

							selecting_mainmenu++;                       // 下へ1マスだけ移動
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

					int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 は「windowTempA」

					int pnCommon = partyNarabijyun[actionOrder[sentoKoudoCount]];



					// デバッグ文
					if (debugFlag == 0) {
						_stprintf_s(mojibuf, TEXT("gte %d"), sentoKoudoCount);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[sentoKoudoCount]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						_stprintf_s(mojibuf, TEXT("pag並び %d"), partyNarabijyun[actionOrder[sentoKoudoCount]]);
						DrawFormatString(battleMassBaseX + 200, battleMassBaseY + 50 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						int pnCommon = partyNarabijyun[actionOrder[sentoKoudoCount]];
						_stprintf_s(mojibuf, TEXT("pnCommon %d"), pnCommon);
						DrawFormatString(battleMassBaseX + 200 + 150, battleMassBaseY + 50 * 4 - 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					} // ここまでデバ文

					// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);




					if (actionOrder[sentoKoudoCount] <= partyNinzuDone - 1) {

						if (heros_def_list[pnCommon].heros_HP0_flag == 0) {

							_stprintf_s(mojibuf, TEXT("%s の攻撃！"), heros_def_list[pnCommon].heros_name);
							DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する




						}
					}


					if (actionOrder[sentoKoudoCount] <= partyNinzuDone - 1) {

						if (heros_def_list[partyNarabijyun[actionOrder[sentoKoudoCount]]].heros_HP0_flag == 1) {


							_stprintf_s(mojibuf, TEXT("%s は戦闘不能で動けない"), heros_def_list[partyNarabijyun[actionOrder[sentoKoudoCount]]].heros_name);
							DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						}
					}



					if (actionOrder[sentoKoudoCount] >= partyNinzuDone) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("敵の攻撃！ "));
						DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}



					// DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "戦うテスト"); // 文字を描画する

					if (PorEflag[sentoKoudoCount] == tekiPE) {
						if (encount_mons_alive == 1) {

							// enemy atack で　tekidame =0 にされてる
							if (damepyon < 10 && tekidame == 0) {
								damepyon = damepyon + 1;
							}

							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d ダメージ"), damage_EnemyAttack);
							DrawFormatString(30, 350 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						}
					}

					if (PorEflag[sentoKoudoCount] == mikataPE) {
						{
							// hero atack で　tekidame =1 にされてる
							if (damepyon < 10 && tekidame == 1) {
								damepyon = damepyon + 1;
							}


							if (heros_def_list[partyNarabijyun[actionOrder[sentoKoudoCount]]].heros_HP0_flag == 0) {
								_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d ダメージ"), damage_HeroAttack);
								DrawFormatString(monX + 10, monY - 30 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // 文字を描画する
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

				// 次行動者(sentoKoudoCount )をセット
				if (battlewait <= 0 && mode_scene == MODE_BATTLE_NOW && dameKei == 1) {
					battlewait = 0;
					dameKei = 0;

					if (monster_hp <= 0) {
						// MessageBox(NULL, TEXT("敵倒した3。"), TEXT("場所テスト"), MB_OK);

						sentouNaninme = 0;
						mode_scene = MODE_BATTLE_WIN;
						battlewait = 60.0 * 2.0;

						// MessageBox(NULL, TEXT("敵倒した。"), TEXT("場所テスト"), MB_OK);
					}
					if (monster_hp > 0) {

						if (sentoKoudoCount <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 && dameKei == 0) {

							// MessageBox(NULL, TEXT("aaa"), TEXT("場所テスト"), MB_OK);

							sentoKoudoCount = sentoKoudoCount + 1;
							battlewait = 60.0 * 2.0;
						}



						// ターン終了					
						if (sentoKoudoCount >= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 + 1) {

							// MessageBox(NULL, TEXT("qwerty"), TEXT("場所テスト"), MB_OK);
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
				} // battlewait が0の状態


				if (mode_scene == MODE_BATTLE_WIN) {

					// MessageBox(NULL, TEXT("敵倒した。"), TEXT("場所テスト"), MB_OK);

					if (partyNinzuDone <= 2) {
						DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "倒した"); // 文字を描画する
					}

					if (partyNinzuDone == 3) {
						DrawFormatString(monMesX + 100, 350 + 30, GetColor(255, 255, 255), "倒した"); // 文字を描画する
					}



					int senkaX = 250; int senkaY = 150;
					window1Draw(senkaX, senkaY, senkaX + 150, senkaY + 120);

					int offsetY2 = FontYoffset;
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Exp: %d"), monster_def_list[encount_monsters_id - 1].mon_exp);
					DrawFormatString(senkaX + 10, senkaY + offsetY2 * 1, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Gold: %d"), monster_def_list[encount_monsters_id - 1].mon_gold);
					DrawFormatString(senkaX + 10, senkaY + offsetY2 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					// debug you
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("mons id: %d"), encount_monsters_id);
					DrawFormatString(senkaX + 10, senkaY + offsetY2 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					keyHaijyo = 1; // 戦闘コマンドが実行されないよう、まだ排除中

					toubouTyokugo[mapEneNum - 1] = 10; // 敵の復活まで残り10カウント
					enemy_alive[mapEneNum - 1] = 0; // 0 だと敵の死亡中の意味


					if (battlewait <= 0 && senkaFlag == 0) {

						sentoKoudoCount = 0; // ターン終了処理

						// MessageBox(NULL, TEXT("敵倒した。"), TEXT("場所テスト"), MB_OK);

						// カネと経験値の更新
						your_money = your_money + monster_def_list[encount_monsters_id - 1].mon_gold;

						for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {

							// 登録キャラが多い場合を想定して（歴史SLGなど）、全キャラは走査しない。							
							// MessageBox(NULL, TEXT("敵倒した。"), TEXT("場所テスト"), MB_OK);

							heros_def_list[partyNarabijyun[temp]].heros_exp = heros_def_list[partyNarabijyun[temp]].heros_exp + monster_def_list[encount_monsters_id - 1].mon_exp;

						}
						senkaFlag = 1;
					}


					if (CheckHitKey(KEY_INPUT_Z) == 1 && senkaFlag == 1) {
						sentoKoudoCount = 0; // ターン終了

						keyEnableReset();
						keyHaijyo = 0;
						mode_scene = MODE_MAP;// テスト用に倒した扱いなので
						senkaFlag = 0; // これないと、以降の戦闘で経験値などが入らなくなる。
					}
				} // win



				// 逃げる
				if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == 2 && keyHaijyo == 0 && mode_scene == MODE_BATTLE_COMMAND) {

					keyHaijyo = 1;

					TimeKasolCount = 0;
					// DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "逃げるのに1成功");  // これは次メッセージで上書きされて消える
					toubouSeikou = 1;
					toubouTyokugo[mapEneNum - 1] = 5;// 敵の復活まで残り5カウント

				}

				if (toubouSeikou == 1) {
					DrawFormatString(monMesX +50, 350 + 30, GetColor(255, 255, 255), "逃げるのに成功"); // 画面に表示されるのは、こっち

				}

				if (toubouSeikou == 1 && TimeKasolCount == 60) {
					keyHaijyo = 0;
					mode_scene = MODE_MAP;
					toubouSeikou = 0; // これないと再戦時に逃亡成功メッセージが出てしまう // 復活時に0セットすると、歩行のたびにセットになるので、こっちでセット
				}
			}


			if (mode_scene == MODE_MENU) {
				int HPX = 300; int HPY = 50;
				int shiftY = 80;
				// ウィンドウ欄

				if (partyNinzuDone < 3) {
					window1Draw(HPX, HPY, HPX + 150, HPY + 100 * 2);
				}

				if (partyNinzuDone >= 3) {
					window1Draw(HPX, HPY, HPX + 150, HPY + 80 * partyNinzuDone);
				}


				for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {
					DrawFormatString(HPX + 20, HPY + 20 * 0 + shiftY * temp, GetColor(255, 255, 255), "%s", heros_def_list[partyNarabijyun[temp]].heros_name); // 文字を描画する			
					DrawFormatString(HPX + 20, HPY + 20 * 1 + shiftY * temp, GetColor(255, 255, 255), "HP %d / %d", heros_def_list[partyNarabijyun[temp]].heros_hp, heros_def_list[partyNarabijyun[temp]].heros_hp_max); // 文字を描画する
					DrawFormatString(HPX + 20 * 3, HPY + 20 * 2 + shiftY * temp, GetColor(255, 255, 255), "EXP %d", heros_def_list[partyNarabijyun[temp]].heros_exp); // 文字を描画する

				}


				window1Draw(480, 380, 600, 470);
				DrawFormatString(500, 400, GetColor(255, 255, 255), "所持金"); // 文字を描画する
				DrawFormatString(500, 400 + 30, GetColor(255, 255, 255), "%d G", your_money); // 文字を描画する


				// コマンドウィンドウの基準位置
				int XXX = 100;  int YYY = 250;
				window1Draw(XXX, YYY, XXX + 150, YYY + 40 + 150);

				if (keyEnableX == 0) {

					DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "カウント %d", nyuuryokuMatiX); // 文字を描画する
					nyuuryokuMatiX = nyuuryokuMatiX - 1;
				}

				if (nyuuryokuMatiX <= 0) {
					keyEnableX = 1;
					nyuuryokuMatiX = 0;

				}


				if (keyEnableX == 1) {
					// 点滅カーソル				
					tenmetu(XXX, YYY + (selecting_mainmenu - 1) * 40, XXX + 80, YYY + (selecting_mainmenu - 1) * 40 + 40);


					// コマンド欄			
					for (int j = 0; j <= 4; ++j) {

						// ここに共通する前段階の作業を記述;

						// 非共通;
						if (j == 0) { lstrcpy(mojibuf, TEXT("道具")); }
						if (j == 1) { lstrcpy(mojibuf, TEXT("装備")); }
						if (j == 2) { lstrcpy(mojibuf, TEXT("技能")); }
						if (j == 3) { lstrcpy(mojibuf, TEXT("セーブ")); }
						if (j == 4) { lstrcpy(mojibuf, TEXT("並び替え")); }

						// ここに共通する後段階の作業を記述;
						DrawFormatString(XXX + 20, YYY + 40 * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}


					// 十字キー入力時
					int rangeMin = 1; int rangeMax = 3;

					// カーソルを上に移動
					{

						// 移動の終了処理

						CheckUPetcFunc();
						if (CheckUPetc) {

							keyEnableUp = 0;
							nyuuryokuMatiUp = waitTime1;

							selecting_mainmenu--;     // 上へ1マスだけ移動

						}


						if (selecting_mainmenu < rangeMin) {
							selecting_mainmenu = rangeMin;
						}

						if (selecting_mainmenu >= rangeMax) {
							selecting_mainmenu = rangeMax;
						}
					}


					// カーソルを下に移動
					{

						// 移動の下降処理
						CheckDOWNetcFunc();
						if (CheckDOWNetc) {

							keyEnableDown = 0;
							nyuuryokuMatiDown = waitTime1;

							selecting_mainmenu++;    // 下へ1マスだけ移動
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
							DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "道具を選びました未実装"); // 文字を描画する

							keyEnableReset();
						}

						if (selecting_mainmenu == 2) {
							mode_scene = MODE_EQUIP_MAIN;
							nyuuryokuMatiZ = waitTime1;

							DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "装備を選びました未実装"); // 文字を描画する
							keyEnableReset();
						}


						if (selecting_mainmenu == 3) {
							MessageBox(NULL, TEXT("特技を使うためのコマンド（※未実装）。"), TEXT("テスト"), MB_OK);

							// 今後の未実装部分なので消すな
							// mode_scene = MODE_SKILL_MAIN;

						}

						if (selecting_mainmenu == 4) {

							mode_scene = MODE_SAVE_MENU;


							// OP画面の設定のセーブ
							FILE* fp1;

							fp1 = fopen("OPSetting.txt", "w");
							{
								fprintf(fp1, "ニューゲームかどうか: %d \n", 2); // 2なら「つづきから」に設定
							}
							fclose(fp1);


							// セーブするよ
							// ゲーム内データのセーブ
							FILE* fp2;
							{
								fp2 = fopen("savedata1.txt", "w");
								if ((fp2 = fopen("savedata1.txt", "w")) == NULL) {
									MessageBox(NULL, TEXT("セーブが失敗しました。対象ファイルが存在しないようです。"), TEXT("メッセージ"), MB_OK);
									break;
								}
								else {
									fprintf(fp2, "現在マップ番号: %d \n", where_map);
									fprintf(fp2, "キャラ位置x座標: %d \n", chara_x);
									fprintf(fp2, "キャラ位置y座標: %d \n", chara_y);


									fprintf(fp2, "パーティ人数: %d \n", partyNinzuDone);
									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "パーティ %d 人目のID: %d \n", temp + 1, partyNarabijyun[temp]);
									}

									fprintf(fp2, "控え人数: %d \n", hikaeNinzu);
									for (int temp = 0; temp <= hikaeNinzu - 1; ++temp) {
										fprintf(fp2, "控え %d 人目のID: %d \n", temp + 1, hikaeNarabijyun[temp]);
									}

									// ロードの都合により、HPのforは最大HPのforとは統合しないこと。
									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "パーティ内キャラ %d 番目の現HP: %d \n", temp + 1, heros_def_list[partyNarabijyun[temp]].heros_hp);
									}

									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "パーティ内キャラ %d 番目の最大HP: %d \n", temp + 1, heros_def_list[partyNarabijyun[temp]].heros_hp_max);
									}


									for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
										fprintf(fp2, "パーティキャラ %d 番目の武器: %d \n", temp + 1, weapon_def_list[
											heros_def_list[partyNarabijyun[temp]].heros_weapon1].def_id);
									}


									// 登録仲間のパラメーター。　一部はパーティパラと重複する
									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "登録キャラ %d 番目の現HP: %d \n", temp + 1, heros_def_list[temp].heros_hp);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "登録キャラ %d 番目の最大HP: %d \n", temp + 1, heros_def_list[temp].heros_hp_max);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "登録キャラ %d 番目の武器: %d \n", temp + 1, weapon_def_list[
											heros_def_list[temp].heros_weapon1].def_id);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "登録キャラ %d 番目の盾: %d \n", temp + 1, shield_def_list[
											heros_def_list[temp].heros_shield].def_id);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "登録キャラ %d 番目の兜: %d \n", temp + 1, helm_def_list[
											heros_def_list[temp].heros_helm].def_id);
									}

									for (int temp = 0; temp <= tourokuNakama; ++temp) {
										fprintf(fp2, "登録キャラ %d 番目の経験値: %d \n", temp + 1, heros_def_list[temp].heros_exp);
									}


									fprintf(fp2, "所持金: %d G\n", your_money);

									char aaa[100];

									// アイテム類の所持数


									// 使用品の所持数
									for (int temp = 0; temp <= 3 - 1; ++temp) {

										//WideCharToMultiByte(CP_ACP, 0, item_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL); // 難しい関数をコピペ用に保管
										fprintf(fp2, "%s の個数: %d \n", aaa, item_have_list[temp].have_kosuu);
									}

									// 装備品の武器の所持数
									for (int temp = 0; temp <= 3 - 1; ++temp) {
										fprintf(fp2, "%s の個数: %d \n", aaa, weapon_have_list[temp].have_kosuu);
									}

									// 装備品の盾の所持数
									for (int temp = 0; temp <= 3 - 1; ++temp) {
										fprintf(fp2, "%s の個数: %d \n", aaa, shield_have_list[temp].have_kosuu);
									}

									// 装備品のカブトの所持数
									for (int temp = 0; temp <= 3 - 1; ++temp) {
										fprintf(fp2, "%s の個数: %d \n", aaa, helm_have_list[temp].have_kosuu);
									}

									fclose(fp2);
								}
							}

							TimeCount = 0;
							mode_scene = MODE_saving_Now; // セーブ終了後にタイマーでしばらく表示。
							// MessageBox(NULL, TEXT("いまここ"), TEXT("メッセージ"), MB_OK);
						}

						if (selecting_mainmenu == 5) {
							// MessageBox(NULL, TEXT("並び替えをするためのコマンド（※未実装）。"), TEXT("テスト"), MB_OK);

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
			} // menu の終わり


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


				// 道具～セーブ のメニュー欄
				int	menuComBaseX = 20; int menuComOffsetPerX = 100;
				int menuComBaseY = 20;

				if (mode_scene == MODE_ITEM_TYPE) {

					for (int j = 0; j <= 2; ++j) {

						// 非共通;
						if (j == 0) { lstrcpy(mojibuf, TEXT("消耗品")); }
						if (j == 1) { lstrcpy(mojibuf, TEXT("装備品")); }
						if (j == 2) { lstrcpy(mojibuf, TEXT("大事なもの")); }

						// ここに共通する後段階の作業を記述;

						DrawFormatString(menuComBaseX + (menuComOffsetPerX + 10) * j, menuComBaseY + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}
				}


				if (mode_scene == MODE_MENU || mode_scene == MODE_ITEM_TYPE) {

					/* 所持金の表示欄 */

					window1Draw(500, 250, 600, 350);

					int GoldViewBaseX = 510; int GoldViewBaseY = 260;

					lstrcpy(mojibuf, TEXT("所持金"));
					DrawFormatString(GoldViewBaseX, GoldViewBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d G"), your_money);
					DrawFormatString(GoldViewBaseX, GoldViewBaseY + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					// _itot_s(your_money , p,200, 10); // 難しい関数なのでコピペ用に残す


					/* キャラのステータス欄 */
					menu_CharaSelectDraw2();

				}


				// 道具～セーブ のメニュー欄
				int XXX = 100;  int YYY = 250;

				int darkWinX = 10; int darkWinY = 250;
				tekidame = 0;

				if (damepyon <= XXX && tekidame == 0) {
					damepyon = damepyon + 5;
				}

				darkwindow1Draw(darkWinX + XXX - damepyon, darkWinY, darkWinX + 110 + XXX - damepyon, darkWinY + 200);
				tenmetuStop(darkWinX, darkWinY, darkWinX + 110, darkWinY + 30);


				for (int j = 0; j <= 4; ++j) {

					// ここに共通する前段階の作業を記述;

					// 非共通;
					if (j == 0) { lstrcpy(mojibuf, TEXT("道具")); }
					if (j == 1) { lstrcpy(mojibuf, TEXT("装備")); }
					if (j == 2) { lstrcpy(mojibuf, TEXT("技能")); }
					if (j == 3) { lstrcpy(mojibuf, TEXT("セーブ")); }
					if (j == 4) { lstrcpy(mojibuf, TEXT("並び替え")); }

					// ここに共通する後段階の作業を記述;
					DrawFormatString(darkWinX + 20, darkWinY + 40 * j, GetColor(255 * 2 / 3, 255 * 2 / 3, 255 * 2 / 3), mojibuf); // 文字を描画する

				}


				if (mode_scene == MODE_ITEM_TYPE) {
					itemList(soubihin, soubiSyoji, 0);

				} // itemlist


				if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {


					if (selecting_mainmenu == 1) {
						// MessageBox(NULL, TEXT("消耗品とか。"), TEXT("キーテスト"), MB_OK);

						selecting_item = 1;
						selecting_item_x = ((selecting_item - 1) % 2) + 1;
						selecting_item_y = ((selecting_item - 1) / 2) + 1;

						mode_scene = MODE_ITEM_MENU; // MODE_ITEM_MENU;

					}


					if (selecting_mainmenu == 2) {
						// MessageBox(NULL, TEXT("装備品の確認。未実装。装備コマンドとは別"), TEXT("テスト"), MB_OK);
						selecting_item = 1;
						selecting_item_x = ((selecting_item - 1) % 2) + 1;
						selecting_item_y = ((selecting_item - 1) / 2) + 1;


						mode_scene = MODE_ITEMweapon_MENU;
					}


					if (selecting_mainmenu == 3) {
						MessageBox(NULL, TEXT("大事なもの（※未実装）。"), TEXT("テスト"), MB_OK);

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
				// カーソルを←に移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
						keyEnableLeft = 0;
						nyuuryokuMatiLeft = waitTime1;
						selecting_mainmenu--;      // 上へ1マスだけ移動

					}


					if (selecting_mainmenu < 0) {
						selecting_mainmenu = 0;
					}

					if (selecting_mainmenu >= itemTypeMax) {
						selecting_mainmenu = itemTypeMax;
					}
				}


				// カーソルをmigi に移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {

						// MessageBox(NULL, TEXT("大事なもの（※未実装）。"), TEXT("テスト"), MB_OK);

						keyEnableRight = 0;
						nyuuryokuMatiRight = waitTime1;

						selecting_mainmenu++;     // 下へ1マスだけ移動
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

				// ここまで、背景フィルターで隠される。

				// Graphics 型の命令の読み込みのためにダミー変数 graphics を宣言.
				//Graphics graphics(hdc);

				// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.
				//graphics.DrawImage(&image1, 0, 0, image1.GetWidth(), image1.GetHeight());

				// 画像の読み込み「image2」は変数名。これが背景フィルター。
				if (filterFlag == 0) {

					//Image image2(L"filter.png");

					// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.

					//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
					filterFlag = 1;
				}

				menu_CharaSelectDraw();
			}





			if (mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) {

				itemList(soubihin, soubiSyoji, 1);
			} // end


			// こっちはボタン操作
			if ((mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) && key_remain > 0) {


				if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

					whatuse = itemHairetu[selecting_item - 1]; //

					key_remain = 0;

					int tempItemPro = 0;
					if (whatuse == -99) {
						tempItemPro = 1;
						// break; // 	DXライブラリだとアプリ終了っぽいのでコメントアウト	
					}

					if (mode_scene == MODE_ITEM_MENU && tempItemPro == 0) {
						mode_scene = MODE_ITEM_WHOM; // 		
					}

					endZ2();
				}


				if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
					//MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);

					mode_scene = MODE_ITEM_TYPE;

					endX();
				}


				// カーソルを上に移動
				{
					// 移動先予定地の入場可否の判定
					CheckUPetcFunc();

					if (CheckUPetc) {
						endUP();

						// 個別の処理
						if (itemHairetu[1] == -99) {
							MessageBox(NULL, TEXT("ueが押されました。"), TEXT("キーテスト"), MB_OK);
							// break; //
						}
						selecting_item = selecting_item - 2; // 方向ごとに違う

						// これはリファクタせずにカッコ内に入れたままにすること if文の外に出せないので
						item_select();
						//moving = 0;

						//MessageBox(NULL, TEXT("ueが押されました。"), TEXT("キーテスト"), MB_OK);

					}
				}


				// カーソルを下に移動
				{
					// 移動先予定地の入場可否の判定
					CheckDOWNetcFunc();
					if (CheckDOWNetc) {
						endDOWN();

						// 個別の処理

						if (itemHairetu[1] == -99) {
							MessageBox(NULL, TEXT("sitaが押されました。"), TEXT("キーテスト"), MB_OK);
							// break; //
						}
						selecting_item = selecting_item + 2; // 方向ごとに違う

						// これはリファクタせずにカッコ内に入れたままにすること
						item_select();
						//moving = 0;
						//MessageBox(NULL, TEXT("sitaが押されました。"), TEXT("キーテスト"), MB_OK);
					}
				}


				// カーソルを右に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {
						keyEnableRight = 0;

						nyuuryokuMatiLR = waitTime1;
						nyuuryokuMatiLeft = waitTime1;
						nyuuryokuMatiRight = waitTime1;

						//
						if (itemHairetu[1] == -99) {
							//break; //
						}
						selecting_item = selecting_item + 1; // 方向ごとに違う

						// これはリファクタせずにカッコ内に入れたままにすること
						item_select();
						//moving = 0;
					}

				}

				// カーソルを左に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
						keyEnableLeft = 0;

						nyuuryokuMatiLR = waitTime1;
						nyuuryokuMatiLeft = waitTime1;
						nyuuryokuMatiRight = waitTime1;

						//
						if (itemHairetu[1] == -99) {
							//break; //
						}
						selecting_item = selecting_item - 1; // 方向ごとに違う

						// これはリファクタせずにカッコ内に入れたままにすること
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
					healflag = 2; // 表示関数で使うので残しておくこと
				}
				if (waitheal <= 0 && healflag != 0) {
					// MessageBox(NULL, TEXT("テスト"), TEXT("キーテスト"), MB_OK);
					waitheal = 0;
					healflag = 0;
				}


				int tempVal;

				if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && key_remain == 1) {

					//MessageBox(NULL, TEXT("いまココ1"), TEXT("メッセージ"), MB_OK);
					keyEnableReset();

					key_remain = 0;
					whomTargetID1 = whomCHARA - 1;
					item_have_list[0].have_kosuu = 0;

					// ここはアイテム使用時の効果

					// 薬草の効果
					if (whatuse == 1) {
						//MessageBox(NULL, TEXT("いまココ1"), TEXT("メッセージ"), MB_OK);		
					}


					// 毒消しの効果
					if (whatuse == 2) {

					}


					// 不死鳥の尾の効果
					if (whatuse == 3) {
						heros_def_list[partyNarabijyun[whomTargetID1]].heros_HP0_flag = 0;

					}


					// 回復の共通処理
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

					// 共通処理 個数ゼロなのに決定ボタンを押したら、アイテム選択に戻る
					if (item_have_list[whatuse].have_kosuu <= 0) {
						mode_scene = MODE_ITEM_MENU;

						//break; // これやると、なぜか強制終了なので、コメントアウト
					}

					// 共通処理 効果の超過分をカット
					if (item_have_list[whatuse].have_kosuu > 0) {


						if (heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp > heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp_max) {
							heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[whomTargetID1].heros_hp_max;
						}


					}


					// 共通処理 個数
					if (item_have_list[whatuse].have_kosuu <= 0) {
						item_have_list[whatuse].have_kosuu = 0;
					}

					nyuuryokuMatiX = waitTime1;
					nyuuryokuMatiZ = waitTime1;
				} // if (CheckHitKey(KEY_INPUT_Z) == 1


				if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0) {
					// MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);
					keyEnableReset();


					filterFlag = 0;
					mode_scene = MODE_ITEM_MENU;

					nyuuryokuMatiX = waitTime1;
					nyuuryokuMatiZ = waitTime1;

				}


				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
					// MessageBox(NULL, TEXT("上が押されました。"), TEXT("キーテスト"), MB_OK);
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
					// MessageBox(NULL, TEXT("↓が押されました。"), TEXT("キーテスト"), MB_OK);
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

			} // アイテム対象者フロントの終わり


			if (mode_scene == MODE_EQUIP_MAIN) {

				// グラフィック関係
				{
					// 装備の表示欄
					// メインモードは装備キャラの選択モードである

					int StatsHPbaseX = 130;
					int StatsHPbaseY = 130;
					int offsetY = 120;

					// 背景の青

					window1Draw(10, 350, 500, 400);

					lstrcpy(mojibuf,
						TEXT("装備を変更するキャラを選んでください。"));

					DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					for (int j = 0; j <= partyNinzuDone - 1; ++j) {
						// 背景の青

						window1Draw(10, 100 + offsetY * j, 300, 200 + offsetY * j);

						// カーソル
						if (whomTargetID1 == j) {

							tenmetu(10, 100 + offsetY * (whomTargetID1),
								300, 200 + offsetY * (whomTargetID1));

						}

						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("%s"),
							heros_def_list[partyNarabijyun[j]].heros_name);

						DrawFormatString(StatsHPbaseX,
							StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						lstrcpy(mojibuf, TEXT("HP"));
						DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("%d"),
							heros_def_list[partyNarabijyun[j]].heros_hp);

						DrawFormatString(StatsHPbaseX + 30,
							StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("/ %d"),
							heros_def_list[partyNarabijyun[j]].heros_hp_max);

						DrawFormatString(StatsHPbaseX + 30 * 2,
							StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						_stprintf_s(
							mojibuf, MAX_LENGTH, TEXT("%d"),
							heros_def_list[partyNarabijyun[j]].heros_HP0_flag);

						DrawFormatString(StatsHPbaseX,
							StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


						if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦闘不能"));

							DrawFormatString(StatsHPbaseX,
								StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						}

						if (debugFlag == 1) {
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("mode: %d"), mode_scene);
							DrawFormatString(130 * 2, 300, GetColor(255, 255, 255), mojibuf); // 文字を描画する
						}
					}

					// そのキャラの装備項目の選択がサブモード

				}// グラフィック関係

				if (keyEnableZ == 0 && nyuuryokuMatiZ >= 0) {
					nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				}

				if (keyEnableZ == 0 && nyuuryokuMatiZ <= 0) {
					keyEnableZ = 1;

					// デバッグ用
					// MessageBox(NULL, TEXT("ここにいる。"), TEXT("キーテスト"), MB_OK);
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

					// MessageBox(NULL, TEXT("上が押されました。"),
				// TEXT("キーテスト"), MB_OK);
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

					// MessageBox(NULL, TEXT("↓が押されました。"),
					// TEXT("キーテスト"), MB_OK);
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

			} // equip モードの終わり



			if (mode_scene == MODE_EQUIP_EDIT || mode_scene == MODE_EQUIP_EDIT2) {
				// 装備の表示欄
				// メインモードは装備キャラの選択モードである
				// MessageBox(NULL, TEXT("aaaaココ1"), TEXT("メッセージ"), MB_OK);


				const int StatsHPbaseX = 130;
				const int StatsHPbaseY = 130;
				int offsetY = 120;


				// 背景の青
				window1Draw(10, 100, 350, 300 + 40);

				// カーソル
				if (mode_scene == MODE_EQUIP_EDIT) {
					tenmetu(90, (110 + 20) + 20 * (whatedit1), 300 - 10,
						(110 + 20) + 20 * (1 + whatedit1));
				}
				if (mode_scene == MODE_EQUIP_EDIT2) {
					tenmetuStop(90, (110 + 20) + 20 * (whatedit1), 300 - 10,
						(110 + 20) + 20 * (1 + whatedit1));
				}


				// 文字
				int soubiYbase = 110; int soubiYper = 20;

				lstrcpy(mojibuf, heros_def_list[partyNarabijyun[whomTargetID1]].heros_name);

				DrawFormatString(15, soubiYbase + soubiYper * 0, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				int stypeOffset = soubiOffset - 1; //10;
				for (int temp = 1; temp <= 7; temp = temp + 1) {

					int afterOffTemp = stypeOffset + temp;

					if (temp == 1) {
						lstrcpy(mojibuf1, TEXT("武器"));
						lstrcpy(mojibuf2,

							soubihin[
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
							].Stype[afterOffTemp].def_name);

					}

					if (temp == 2) {
						lstrcpy(mojibuf1, TEXT("盾"));
						lstrcpy(mojibuf2,

							soubihin[
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
							].Stype[afterOffTemp].def_name);
					}

					if (temp == 3) {
						lstrcpy(mojibuf1, TEXT("頭"));
						lstrcpy(mojibuf2,
							soubihin[
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
							].Stype[afterOffTemp].def_name);

					}

					if (temp == 4) {
						lstrcpy(mojibuf1, TEXT("身体"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					if (temp == 5) {
						lstrcpy(mojibuf1, TEXT("腕"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					if (temp == 6) {
						lstrcpy(mojibuf1, TEXT("装飾品1"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					if (temp == 7) {
						lstrcpy(mojibuf1, TEXT("装飾品2"));
						lstrcpy(mojibuf2, TEXT("--------"));
					}

					DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // 文字を描画する
					DrawFormatString(90, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // 文字を描画する

				}

				int temp = 8;

				lstrcpy(mojibuf1, TEXT("攻撃力"));
				DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // 文字を描画する

				_stprintf_s(mojibuf2, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[kougekiPara]);
				DrawFormatString(90 + 50, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // 文字を描画する


				temp = 9;
				lstrcpy(mojibuf1, TEXT("守備力"));
				DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // 文字を描画する

				_stprintf_s(mojibuf2, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[syubiPara]);
				DrawFormatString(90 + 50, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // 文字を描画する


				// たぶんウィンドウ背景の青
				window1Draw(10, 350, 500, 400);

				lstrcpy(mojibuf, TEXT("変更したい装備を選んでください。"));
				DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				if (mode_scene == MODE_EQUIP_EDIT) {
					int locType;

					locType = soubiOffset + whatedit1;
					/*
					// 下記は上記のリファクタ

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

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), 0); // 未定義エラーを防ぐための初期化

					if (locType == wepoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[tempSoubi].Stype[locType]).equipPower[kougekiPara]);
					}
					if (locType == tateType || locType == kabutoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[tempSoubi].Stype[locType]).equipPower[syubiPara]);
					}

					DrawFormatString(15 + 300 * 0, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}


				if (debugFlag == 1) {
					// デバッグ文。装備個数ズレのバグ調査。
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("whatedit2: %d"), whatedit2);
					DrawFormatString(15, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("iHw2: %d"), itemHairetu[whatedit2]);
					DrawFormatString(15 + 130, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("wHL: %d"), weapon_have_list[heros_def_list[partyNarabijyun[whomTargetID1]].heros_weapon1].have_def_id);
					DrawFormatString(15 + 130 + 100, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

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
							// MessageBox(NULL, TEXT("いまココ1"), TEXT("メッセージ"), MB_OK);

							key_remain = 0;
							whomTargetID1 = whomCHARA - 1;

							whatedit2 = 0;

							mode_scene = MODE_EQUIP_EDIT2;


							mode2_scene = MODE2_EQUIP_UnDef; // 未定義対応のため、とりあえず武器に初期化
							mode3_scene = 0;


							mode3_scene = whatedit1 + 11; // 装備品データベースは11番から
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

							// MessageBox(NULL, TEXT("上が押されました。"),
						// TEXT("キーテスト"), MB_OK);
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
							// MessageBox(NULL, TEXT("↓が押されました。"),
							// TEXT("キーテスト"), MB_OK);
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

					// 装備用アイテムのリスト表示
					// 背景の青

					window1Draw(souWInXsta, 100, souWInXend, 300);

					tenmetu(souWInXsta + 20, (110 + 20) + 20 * (whatedit2), souWInXend - 30,
						(110 + 20) + 20 * (1 + whatedit2));

					weapon_have_list[0].have_kosuu = 0;


					// 移植中
					int itemskip = 0;
					goukeiItem = 0;

					int itemIDcount = 0;
					int column = 1; // 装備コマンドの武器防具リストは1行なので

					int xcommon;
					int ycommon;


					int locType;
					locType = mode3_scene;

					{

						// idTemp は装備品種類に対応. 0 が武器, 1がタテ 
						for (idTemp = 0; idTemp <= 2; idTemp = idTemp + 1)
						{
							itemHairetu[idTemp] = 0; // これないと、装備品が減ったとき残骸が残る。[]内がidTempであることに注意
						}

						for (idTemp = 0; idTemp <= 2; idTemp = idTemp + 1)
						{

							if ((soubiSyoji[idTemp].Stype[locType]).have_kosuu != 0) {

								xcommon = souWInXsta + 300 * floor((idTemp - itemskip) % column);
								ycommon = 130 + 20 * floor((idTemp - itemskip) / column);

								// アイテム名の表示
								lstrcpy(mojibuf, (soubihin[idTemp].Stype[locType]).def_name);
								DrawFormatString(xcommon, ycommon, GetColor(255, 255, 255), mojibuf); // 文字を描画する

								// 個数の表示
								_stprintf_s(mojibuf, MAX_LENGTH, TEXT("x %d"), (soubiSyoji[idTemp].Stype[locType]).have_kosuu);
								DrawFormatString(xcommon + 130, ycommon, GetColor(255, 255, 255), mojibuf); // 文字を描画する


								goukeiItem = goukeiItem + 1;

								itemHairetu[itemIDcount] = idTemp; // これはボタン操作側で使う
								itemIDcount = itemIDcount + 1; // これは上コードで使う

							}

							if ((soubiSyoji[idTemp].Stype[locType]).have_kosuu == 0) {
								itemskip = itemskip + 1;
								itemHairetu[itemIDcount] = 0; // これないと、装備部位を変えたとき残骸が残る。
							}
						}

						CheckUPetcFunc();
						if (CheckUPetc) {

							// MessageBox(NULL, TEXT("上が押されました。"),
						// TEXT("キーテスト"), MB_OK);
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
								// 攻撃力の更新
								heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[kougekiPara] =
									(soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[kougekiPara];

							}
							sentakuKougekiR = (soubihin[itemHairetu[whatedit2]].Stype[wepoType]).equipPower[kougekiPara]; // 表示でも使うので再利用

							(soubiSyoji[hensu].Stype[locType]).have_kosuu =
								(soubiSyoji[hensu].Stype[locType]).have_kosuu + 1; // 装備してた武器が1個増えるように


							if (whatedit2 < goukeiItem) {

								//itemHairetu
								(soubiSyoji[itemHairetu[whatedit2]].Stype[locType]).have_kosuu
									= (soubiSyoji[itemHairetu[whatedit2]].Stype[locType]).have_kosuu - 1; // 


							}
							if (whatedit2 >= goukeiItem) {
								// 何も選択してない状態なので、何も減らない
								//weapon_have_list[whatedit2 + 1].have_kosuu = weapon_have_list[whatedit2 + 1].have_kosuu - 1;  // カーソル選択中だった武器が1個減る
							}


							if (whatedit2 < goukeiItem) {
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType] =

									soubihin[itemHairetu[whatedit2]].Stype[locType].def_id; // 

							}
							if (whatedit2 >= goukeiItem) {
								heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType] =
									soubihin[0].Stype[locType].def_id; // 装備の更新をしたい
							}



							/////////////

							if (locType == tateType || locType == kabutoType) {

								// 防具の更新 // すでにしてある

								//(soubihin[heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType]].Stype[locType]).equipPower[syubiPara] =
								//	(soubihin[heros_def_list[itemHairetu[whatedit2]].heroSoubi[locType]].Stype[locType]).equipPower[syubiPara]
								//	;


								// 防御力の更新
								heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[syubiPara] = // 現在の値

									(soubihin[(heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[tateType])].Stype[tateType]).equipPower[syubiPara]
									+ (soubihin[(heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[kabutoType])].Stype[kabutoType]).equipPower[syubiPara]
									;

							}

							//////////

							(soubiSyoji[0].Stype[locType]).have_kosuu = 0;

						}

					} // ウェポン

				}

				if (mode_scene == MODE_EQUIP_EDIT2) {

					int locType;
					locType = mode3_scene;

					_stprintf_s(mojibuf, MAX_LENGTH, TEXT(""), 0); // 未定義エラー文を防ぐための初期化

					if (locType == wepoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[kougekiPara]);
					}

					if (locType == tateType || locType == kabutoType) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[syubiPara]);
					}

					DrawFormatString(15 + 300, 350 + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}
			} // end of MODE_EQUIP_ 手～頭


			if (mode_scene == skillMode) {

				CheckXetcFunc();
				if (CheckXetc) {
					mode_scene = MODE_MENU;

					endX2();

					DrawFormatString(250, 250 + 50 * 2, GetColor(255, 255, 255), "特技から戻り"); // 文字を描画する

				}
			}

			key_remain = 1;

			ScreenFlip(); //裏画面を表画面に反映
		}

	}


	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 


}

