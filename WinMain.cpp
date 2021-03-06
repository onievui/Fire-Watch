//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   WinMain.cpp
//!
//! @brief  ゲームプログラムのエントリーポイントのソースファイル
//!
//! @date   2017/3/17
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "Game\GameMain.h"
#include "Resources\Icon\Icon.h"




// 関数定義 ================================================================

//----------------------------------------------------------------------
//! @brief プログラムのエントリーポイント
//!
//! @param[in] hInstance     現在のインスタンスのハンドル
//! @param[in] hPrevInstance 以前のインスタンスのハンドル(常にNULL)
//! @param[in] lpCmdLine     コマンドライン
//! @param[in] nCmdShow      ウィンドウの表示状態
//!
//! @retval  0 正常終了
//! @retval -1 異常終了
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 未使用引数の警告対策
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


#if defined(_DEBUG)
	// メモリーリーク検出機構のセットアップ
	// SetUpMemoryLeakDetector();
#endif


	// デバッグ情報用ログファイルの出力の抑制
	SetOutApplicationLogValidFlag(FALSE);


	// 起動モードの設定
#if defined(_DEBUG)
	ChangeWindowMode(TRUE);	          // ウインドウモードで実行
	SetMainWindowText(GAME_TITLE);    // ウインドウタイトルの設定
	SetWindowIconID(IDI_ICON1);       // ウインドウアイコンの設定
#else
	ChangeWindowMode(FALSE);	      // フルスクリーンで実行
#endif

	// 使用する Direct3D のバージョンを 9EX に設定
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);

	// 初期状態の画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// DXライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;    // エラーが起きたら直ちに終了
	}


	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームオブジェクトの生成
	Game* game = new Game;

	// ゲームの処理
	game->initialize();    // ゲームの初期化処理
	
	while (!ProcessMessage() && !CheckHitKey(EXIT_KEY))
	{ 
		game->update();          // ゲームの更新処理
		game->render();          // ゲームの描画処理

		ScreenFlip();          // 裏画面の内容を表画面に反映
		ClearDrawScreen();     // 裏画面の消去
	}

	game->finalize();      // ゲームの終了処理

	// ゲームオブジェクトの破棄
	delete game;

	// DXライブラリの終了処理
	DxLib_End();


	return 0;    // 正常終了
}
