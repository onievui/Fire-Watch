//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibGraphics.cpp
//!
//! @brief  グラフィック関連の機能のソースファイル
//!
//! @date   2018/10/20
//!
//! @author S.Takaki
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameLibGraphics.h"

#include <cmath>
#include <cstdio>

#include <DxLib.h>




// 定数の定義 ==============================================================
const int NUM_CAPSULE_DIVISION = 16;    // カプセル描画における半円の分割数




// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief 破線を描画
//!
//! @param[in] x1        描画する線の起点座標(X座標)
//! @param[in] y1        描画する線の起点座標(Y座標)
//! @param[in] x2        描画する線の終点座標(X座標)
//! @param[in] y2        描画する線の終点座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] length    破線の長さおよび間隔の幅
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness)
{
	int vx = x2 - x1;
	int vy = y2 - y1;

	double angle = atan2(vy, vx);
	float dx = static_cast<float>(length * cos(angle));
	float dy = static_cast<float>(length * sin(angle));

	int count = static_cast<int>(sqrt(vx * vx + vy * vy) / length);

	float x = static_cast<float>(x1);
	float y = static_cast<float>(y1);

	for (int i = 0; i < count; i += 2)
	{
		if (DrawLine(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + dx), static_cast<int>(y + dy), color, thickness) == -1)
		{
			return -1;
		}
		x += dx * 2;
		y += dy * 2;
	}

	if (count % 2 == 0)
	{
		if (DrawLine(static_cast<int>(x), static_cast<int>(y), x2, y2, color, thickness) == -1)
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief 破線を描画(アンチエイリアス効果付き)
//!
//! @param[in] x1        描画する線の起点座標(X座標)
//! @param[in] y1        描画する線の起点座標(Y座標)
//! @param[in] x2        描画する線の終点座標(X座標)
//! @param[in] y2        描画する線の終点座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] length    破線の長さおよび間隔の幅
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness)
{
	float vx = x2 - x1;
	float vy = y2 - y1;

	double angle = atan2(vy, vx);
	float dx = static_cast<float>(length * cos(angle));
	float dy = static_cast<float>(length * sin(angle));

	int count = static_cast<int>(sqrt(vx * vx + vy * vy) / length);

	float x = x1;
	float y = y1;

	for (int i = 0; i < count; i += 2)
	{
		if (DrawLineAA(x, y, (x + dx), (y + dy), color, thickness) == -1)
		{
			return -1;
		}
		x += dx * 2;
		y += dy * 2;
	}

	if (count % 2 == 0)
	{
		if (DrawLineAA(x, y, x2, y2, color, thickness) == -1)
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief カプセルを描画
//!
//! @param[in] x1        一方の円の中心座標(X座標)
//! @param[in] y1        一方の円の中心座標(Y座標)
//! @param[in] x2        もう一方の円の中心座標(X座標)
//! @param[in] y2        もう一方の円の中心座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int DrawCapsule(int x1, int y1, int x2, int y2, int r, unsigned int color, int thickness)
{
	int vx = x2 - x1;
	int vy = y2 - y1;

	double angle = atan2(vy, vx) + (DX_PI / 2);

	float dx[NUM_CAPSULE_DIVISION + 1];
	float dy[NUM_CAPSULE_DIVISION + 1];
	int i;

	for (i = 0; i < NUM_CAPSULE_DIVISION + 1; i++)
	{
		dx[i] = static_cast<float>(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
		dy[i] = static_cast<float>(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
	}


	if (DrawLine(static_cast<int>(x1 + dx[0]), static_cast<int>(y1 + dy[0]), static_cast<int>(x2 + dx[0]), static_cast<int>(y2 + dy[0]), color, thickness))
	{
		return -1;
	}

	if (DrawLine(static_cast<int>(x1 + dx[NUM_CAPSULE_DIVISION]), static_cast<int>(y1 + dy[NUM_CAPSULE_DIVISION]), static_cast<int>(x2 + dx[NUM_CAPSULE_DIVISION]), static_cast<int>(y2 + dy[NUM_CAPSULE_DIVISION]), color, thickness))
	{
		return -1;
	}


	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLine(static_cast<int>(x1 + dx[i]), static_cast<int>(y1 + dy[i]), static_cast<int>(x1 + dx[i + 1]), static_cast<int>(y1 + dy[i + 1]), color, thickness))
		{
			return -1;
		}
	}

	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLine(static_cast<int>(x2 - dx[i]), static_cast<int>(y2 - dy[i]), static_cast<int>(x2 - dx[i + 1]), static_cast<int>(y2 - dy[i + 1]), color, thickness))
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief カプセルを描画(アンチエイリアス効果付き)
//!
//! @param[in] x1        一方の円の中心座標(X座標)
//! @param[in] y1        一方の円の中心座標(Y座標)
//! @param[in] x2        もう一方の円の中心座標(X座標)
//! @param[in] y2        もう一方の円の中心座標(Y座標)
//! @param[in] color     描く線の色
//! @param[in] thickness 線の太さ
//!
//! @retval  0 成功
//! @retval -1 エラー発生
//----------------------------------------------------------------------
int DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, unsigned int color, float thickness)
{
	float vx = x2 - x1;
	float vy = y2 - y1;

	double angle = atan2(vy, vx) + (DX_PI / 2);

	float dx[NUM_CAPSULE_DIVISION+1];
	float dy[NUM_CAPSULE_DIVISION+1];
	int i;

	for (i = 0; i < NUM_CAPSULE_DIVISION+1; i++)
	{
		dx[i] = static_cast<float>(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
		dy[i] = static_cast<float>(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
	}


	if (DrawLineAA(x1 + dx[0], y1 + dy[0], x2 + dx[0], y2 + dy[0], color, thickness))
	{
		return -1;
	}

	if (DrawLineAA(x1 + dx[NUM_CAPSULE_DIVISION], y1 + dy[NUM_CAPSULE_DIVISION], x2 + dx[NUM_CAPSULE_DIVISION], y2 + dy[NUM_CAPSULE_DIVISION], color, thickness))
	{
		return -1;
	}


	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLineAA(x1 + dx[i], y1 + dy[i], x1 + dx[i + 1], y1 + dy[i + 1], color, thickness))
		{
			return -1;
		}
	}

	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
	{
		if (DrawLineAA(x2 - dx[i], y2 - dy[i], x2 - dx[i + 1], y2 - dy[i + 1], color, thickness))
		{
			return -1;
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief 画像ファイルのメモリへの読みこみ(エラー処理付き)
//!
//! @param[in] filename 読み込み対象の画像ファイルの名前
//!
//! @retval -1以外 グラフィックのハンドル
//! @retval -1     エラー発生
//----------------------------------------------------------------------
int LoadGraphWithErrorHandling(const char* filename)
{
	HGRP imageHandle = LoadGraph(filename);

	if (imageHandle == -1)
	{
		char errorMessage[MAX_PATH];
		snprintf(errorMessage, sizeof(errorMessage), "以下のファイルが見つかりません。\n\"%s\"", filename);
		MessageBox(NULL, errorMessage, NULL, MB_OK | MB_ICONEXCLAMATION);
		ExitGame();
	}

	return imageHandle;
}
