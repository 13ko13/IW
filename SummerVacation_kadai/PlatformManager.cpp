#include "PlatformManager.h"
#include "DxLib.h"
#include <algorithm>
#include "FallPlatTrap.h"

PlatformManager::PlatformManager() : m_graphHandle(-1)
{
}

PlatformManager::~PlatformManager() 
{
}

void PlatformManager::Init(int graphHandle)
{
    m_graphHandle = graphHandle;
}


void PlatformManager::Update(const Rect& playerRect)
{
    for (auto& platform : m_platforms) {
        platform.Update(playerRect);
    }

    m_platforms.erase(
        std::remove_if(m_platforms.begin(), m_platforms.end(),
            [](const FallPlatTrap& platform) {
                return !platform.IsActive(); // 非アクティブなら削除
            }),
        m_platforms.end()
    );
}


void PlatformManager::Draw()
{
    for (auto& platform : m_platforms)
    {
        platform.Draw();
    }
}

void PlatformManager::SpawnPlatform(const Vec2& pos, int delayFrames)
{
    FallPlatTrap platform;
    platform.Init(pos, delayFrames, m_graphHandle);
    m_platforms.push_back(platform);
}

bool PlatformManager::CheckCollision(const Rect& playerRect) const
{
    for (const auto& platform : m_platforms) {
        if (platform.IsActive() && platform.GetRect().IsCollision(playerRect)) {
            return true;
        }
    }
    return false;
}