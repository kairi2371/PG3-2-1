#include <functional>

class Enemy {
public:
    enum State {
        APPROACH,
        SHOOT,
        WITHDRAW
    };

    using StateFunction = std::function<void(Enemy&)>;

    // 初期状態は接近
    Enemy() : currentState(&Enemy::Approach) {}

    // 状態遷移を実行する関数
    void Update(State state) {
        (this->spFuncTable[state])(*this);
    }

private:
    // 状態遷移用のメンバ関数ポインタ
    StateFunction currentState;

    // 接近状態
    void Approach() {
        printf("Enemy is approaching.\n");

        // 何らかの条件で射撃に遷移
        currentState = &Enemy::Shoot;
    }

    // 射撃状態
    void Shoot() {
        printf("Enemy is shooting.\n");
        currentState = &Enemy::Withdraw;
    }

    // 離脱状態
    void Withdraw() {
        printf("Enemy is withdrawing.\n");
        currentState = &Enemy::Approach;
    }

    // メンバ関数ポインタ
    StateFunction spFuncTable[3] = {
        &Enemy::Approach,
        &Enemy::Shoot,
        &Enemy::Withdraw
    };
};

int main() {
    Enemy enemy;

    for (int i = 0; i < 5; ++i) {
        enemy.Update(Enemy::SHOOT);
    }

    return 0;
}