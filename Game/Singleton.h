#pragma once

#include <memory>

template <typename T>

/// <summary>
/// シングルトンクラステンプレート
/// </summary>
class Singleton {
protected:
	Singleton() = default;
	virtual~Singleton() = default;

public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	static T* getIns() {
		static T instance;
		return &instance;
	}
};