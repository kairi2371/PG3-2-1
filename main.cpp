#include <functional>

class Enemy {
public:
    enum State {
        APPROACH,
        SHOOT,
        WITHDRAW
    };

    using StateFunction = std::function<void(Enemy&)>;

    // ������Ԃ͐ڋ�
    Enemy() : currentState(&Enemy::Approach) {}

    // ��ԑJ�ڂ����s����֐�
    void Update(State state) {
        (this->spFuncTable[state])(*this);
    }

private:
    // ��ԑJ�ڗp�̃����o�֐��|�C���^
    StateFunction currentState;

    // �ڋߏ��
    void Approach() {
        printf("Enemy is approaching.\n");

        // ���炩�̏����Ŏˌ��ɑJ��
        currentState = &Enemy::Shoot;
    }

    // �ˌ����
    void Shoot() {
        printf("Enemy is shooting.\n");
        currentState = &Enemy::Withdraw;
    }

    // ���E���
    void Withdraw() {
        printf("Enemy is withdrawing.\n");
        currentState = &Enemy::Approach;
    }

    // �����o�֐��|�C���^
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