#include "timer_manager.h"  /*! Header file */
#include "Public/time_manager.h"   /*! opgs16::manager::TimeManager */

size_t TimerManager::s_timer_count = 0;

void TimerManager::Update() {
    auto time_quantum = opgs16::manager::TimeManager::Instance().GetDeltaTime();

    /*! Iteration & Checking */
    for (auto& timer : m_timer_container) {
        if (timer.second.m_status == Status::ACTIVATED)
            timer.second.m_handle->Try(time_quantum);
    }

    /*! Deletion */
    for (const auto& i : m_delete_list) {
        m_timer_container.erase(i);
    }
}

void TimerManager::Clear() {
    s_timer_count = 0u;
    m_delete_list.clear();
    m_timer_container.clear();
}

bool TimerManager::PauseTimer(TimerHandle& handle) {
    auto key = handle.GetKeyValue();
    if (m_timer_container.find(key) != m_timer_container.end() &&
        m_timer_container.at(key).m_status == Status::ACTIVATED) {
        m_timer_container.at(key).m_status = Status::PAUSED;

        return true;
    }
    else return false;
}

bool TimerManager::ResumeTimer(TimerHandle& handle) {
    auto key = handle.GetKeyValue();
    if (m_timer_container.find(key) != m_timer_container.end() &&
        m_timer_container.at(key).m_status == Status::PAUSED) {
        m_timer_container.at(key).m_status = Status::ACTIVATED;

        return true;
    }
    else return false;
}

bool TimerManager::DetachTimer(TimerHandle& handle) {
    auto key = handle.GetKeyValue();
    if (m_timer_container.find(key) != m_timer_container.end()) {
        m_timer_container.at(key).m_status = Status::REMOVED;
        m_delete_list.emplace_back(key);        /*! and add key to candidate list to destroy */
                                                /*! pointer */
        return true;
    }
    else return false;
}