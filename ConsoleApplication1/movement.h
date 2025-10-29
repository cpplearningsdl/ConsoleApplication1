#pragma once
#include <cmath>
#include "json.hpp"
#include "logManager.h"
#include "position.h"

class movement {
public:
	struct movementData {
		position pos = { -1,-1 };      // current position
		position dest = { -1,-1 };     // destination
		position delta;    // per-step movement vector
		float speed{ 1.0f };
	};

private:
	movementData data;

public:
	movement() = default;

	movement(float startX, float startY, float targetX, float targetY, float moveSpeed) {
		init({ startX, startY }, { targetX, targetY }, moveSpeed);
	}

	movement(const position& start, const position& target, float moveSpeed) {
		init(start, target, moveSpeed);
	}
	void clear() {
		init({ 0,0 }, { 0,0 }, 1.0f);
	}
	void init(const position& start, const position& target, float moveSpeed) {
		data.pos = start;
		data.dest = target;
		data.speed = (moveSpeed > 0.0f) ? moveSpeed : 1.0f;

		float dx = data.dest.getX() - data.pos.getX();
		float dy = data.dest.getY() - data.pos.getY();
		float length = std::sqrt(dx * dx + dy * dy);

		if (length != 0.0f) {
			data.delta.setX((dx / length) * data.speed);
			data.delta.setY((dy / length) * data.speed);
		}
		else {
			data.delta.setX(0.0f);
			data.delta.setY(0.0f);
		}
	}

	void step() {
		float dx = data.dest.getX() - data.pos.getX();
		float dy = data.dest.getY() - data.pos.getY();
		float distance = std::sqrt(dx * dx + dy * dy);

		if (distance > data.speed) {
			data.pos.setX(data.pos.getX() + data.delta.getX());
			data.pos.setY(data.pos.getY() + data.delta.getY());
		}
		else {
			data.pos.setX(data.dest.getX());
			data.pos.setY(data.dest.getY());
		}

		logManager::logThis(
			"X: " + std::to_string(data.pos.getX()) +
			", Y: " + std::to_string(data.pos.getY())
		);
	}

	bool isFinished() const {
		return (data.pos.getX() == data.dest.getX() &&
			data.pos.getY() == data.dest.getY());
	}
	// --- Getters ---
	const position& getPos() const { return data.pos; }
	const position& getDest() const { return data.dest; }
	const position& getDelta() const { return data.delta; }
	float getSpeed() const { return data.speed; }

	float getX() const { return data.pos.getX(); }
	float getY() const { return data.pos.getY(); }
	float getDestX() const { return data.dest.getX(); }
	float getDestY() const { return data.dest.getY(); }
	float getDeltaX() const { return data.delta.getX(); }
	float getDeltaY() const { return data.delta.getY(); }

	// --- Setters ---
	void setPos(const position& p) { data.pos = p; }
	void setDest(const position& d) { data.dest = d; }
	void setDelta(const position& d) { data.delta = d; }
	void setSpeed(float s) { data.speed = s; }

	void setX(float x) { data.pos.setX(x); }
	void setY(float y) { data.pos.setY(y); }
	void setDestX(float x) { data.dest.setX(x); }
	void setDestY(float y) { data.dest.setY(y); }

	// --- Serialization ---
	friend void to_json(nlohmann::ordered_json& j, const movement& move);
	friend void from_json(const nlohmann::ordered_json& j, movement& move);
};

// --- JSON conversion ---
inline void to_json(nlohmann::ordered_json& j, const movement& move) {
	j["movement"] = {
		{ "pos", move.data.pos },
		{ "dest", move.data.dest },
		{ "delta", move.data.delta },
		{ "speed", move.data.speed }
	};
}

inline void from_json(const nlohmann::ordered_json& j, movement& move) {
	const auto& obj = j.at("movement");

	obj.at("pos").get_to(move.data.pos);
	obj.at("dest").get_to(move.data.dest);
	obj.at("delta").get_to(move.data.delta);
	move.data.speed = obj.value("speed", 1.0f);
}
