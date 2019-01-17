//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLib.h
//!
//! @brief  ゲーム制作用ライブラリのヘッダファイル
//!
//! @date   2018/10/20
//!
//! @author onievui
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// ヘッダファイルの読み込み ================================================
#include <DxLib.h>

#include "GameLibAudio.h"
#include "GameLibCollision.h"
#include "GameLibGraphics.h"
#include "GameLibInput.h"
#include "GameLibMath.h"
#include "GameLibScreen.h"
#include "GameLibSystem.h"
#include "GameLibTime.h"




// 型の定義 ================================================================
using HGRP = int;    // グラフィックハンドル     
using HSND = int;    // サウンドハンドル
using HFNT = int;    // フォントハンドル
using HNET = int;    // ネットワークハンドル 
