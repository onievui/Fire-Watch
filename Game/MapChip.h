#pragma once



/// <summary>
/// マップチップクラス
/// </summary>
class MapChip {
private:
	HGRP texture;			//テクスチャ
	bool isPassableFlag;	//通行可能かどうか

public:
	MapChip(const HGRP _texture, const bool _is_passable);
	~MapChip();

public:
	void render(int _x, int _y, int _grid_size) const;
	bool isPassable() const;
};
