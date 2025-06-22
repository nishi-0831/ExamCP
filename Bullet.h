#pragma once
#include "GameObject.h"
#include "global.h"
#include <vector>
#include <memory>
#include <algorithm>



//玉のサイズは13.0fと33.0f
class Bullet : public GameObject
{
public:
    Bullet();
    Bullet(Shooter shooter);
    Bullet(float x, float y, Shooter shooter);
    Bullet(float x, float y, Shooter shooter, PointF dir);

    ~Bullet();
    // Reset メソッドのオーバーロード
    void Reset();  // デフォルトリセット
    void Reset(Shooter shooter);  // シューターのみ指定
    void Reset(float x, float y, Shooter shooter);  // 位置とシューター指定
    void Reset(float x, float y, Shooter shooter, PointF dir);  // 全
    void Update() override;
    void Draw() override;

    void SetPos(float x, float y);
    void SetFired(bool fired) { isFired_ = fired; }
    void SetDir(PointF dir);
    bool IsFired() const { return isFired_; }
    Shooter GetShooter() { return shooter_; }
    void RegisterToManager();
private:
    Shooter shooter_;
    PointF dir_;
    float speed_;
    bool isFired_;//発射されているかどうか
};
class BulletManager {
private:
    static BulletManager* instance_;
    std::vector<std::weak_ptr<class Bullet>> bullets_;
    const int MAX_BULLET_NUM = 30;
    BulletManager() = default;

public:
    static BulletManager* GetInstance() {
        if (!instance_) {
            instance_ = new BulletManager();
        }
        return instance_;
    }
    template<typename... Args>
    void RegisterBullet(Args&&... args);
    /*void RegisterBullet(std::shared_ptr<Bullet> bullet)
    {
        if (bullets_.size() >= MAX_BULLET_NUM)
        {
            bullet.reset();
            return;
        }
        bullets_.push_back(bullet);
    }*/

    void Cleanup();

    const std::vector<std::weak_ptr<Bullet>>& GetAllBullets() const {
        return bullets_;
    }
};
template<typename... Args>
void BulletManager::RegisterBullet(Args&&... args)
{
    Cleanup();
    if (bullets_.size() < MAX_BULLET_NUM)
    {
        std::shared_ptr<Bullet> bullet = GameObject::CreateGameObject<Bullet>(std::forward<Args>(args)...);
        bullets_.push_back(bullet);
    }
    else
    {
        for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
            if (auto bullet = it->lock()) {
                if (bullet->IsAlive() && !bullet->IsFired())
                {
                    bullet->Reset(std::forward<Args>(args)...);

                    return;//一個だけ再利用
                }
            }
        }

        //未使用の弾が見つからなかったら何もしない
    }

}