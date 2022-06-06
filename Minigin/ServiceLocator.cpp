#include "MiniginPCH.h"
#include "ServiceLocator.h"

Empty_Sound_System ServiceLocator::m_defaultSs;
SoundSystem* ServiceLocator::m_pSsInstance = &m_defaultSs;

SoundSystem& ServiceLocator::GetSoundSystem()
{
    return *m_pSsInstance;
}

void ServiceLocator::RegisterSoundSystem(SoundSystem* ss)
{
    m_pSsInstance = ss == nullptr ? &m_defaultSs : ss;
}

void ServiceLocator::ReleaseSoundSystem()
{
    delete m_pSsInstance;
    m_pSsInstance = nullptr;
}
