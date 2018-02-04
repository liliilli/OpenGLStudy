#include "pp_manager.h"
#include "PostProcessing\pp_scaling.h"
#include "..\..\application.h"

namespace shading {

using PPManager = PostProcessingManager;
PostProcessingManager::PostProcessingManager() {
	InsertEffectInitiate<shading::PpEffectScaling>("__df__");
}

PPManager::pp_effect& PostProcessingManager::GetEffect(const std::string&& tag) {
	if (IsEffectExist(tag)) return m_effects.at(tag);
}

bool PostProcessingManager::InsertEffect(const std::string& tag) {
	return InsertEffect<shading::PostProcessingFrame>(tag);
}

using sequence_type = PostProcessingManager::sequence_type;
const sequence_type* const
PostProcessingManager::SetSequence(const size_t id,
								   const std::initializer_list<std::string>& list) {
	/** Body */
	if (!IsEffectSequenceAlreadyExist(id)) {
		std::list<ppf_ptr>&& effect_list{};
		for (const auto& tag : list) {
			if (IsEffectExist(tag)) {
				// Push and get count up.
				effect_list.push_back(GetEffect(std::string{ tag }).get());
				(*effect_list.rbegin())->Active();
			}
			else return nullptr;
		}
		// Insert
		m_effect_sequences[id] = std::move(effect_list);
		return &m_effect_sequences[id];
	}
	else return nullptr;
}

void PostProcessingManager::UpdateSequences() {
	for (auto& effect : m_effects) {
		auto& item = effect.second;
		if (item->IsActive()) item->Update();
	}
}

void PostProcessingManager::BindSequence(const size_t id) {
	if (IsEffectSequenceAlreadyExist(id)) {
		m_binded_number = id;
		/** Bind first */
		(*m_effect_sequences.at(id).begin())->Bind();
	}
}

void PostProcessingManager::RenderSequence() {
	if (m_binded_number != m_reset) {
		auto& list = m_effect_sequences.at(m_binded_number);
		/** Iterate effect list, and rendering */
		auto it_effect = list.begin();
		auto it_rbegin = (--list.end());

		std::for_each(list.begin(), list.end(), [&](decltype(*it_effect)& effect) {
			if (it_effect != it_rbegin) /** If this is not end of sequence, bind next. */ {
				(*std::next(it_effect))->Bind();
			}
			else { /** Bind to scaling frame buffer */
				m_effects.at("__df__")->Bind();
			}

			/** Render! */
			effect->RenderEffect();
			it_effect++;
		});
	}
}

void PostProcessingManager::ReleaseSequence(const size_t id) {
	if (m_effect_sequences.find(id) != m_effect_sequences.end()) {
		if (m_binded_number == id) m_binded_number = m_reset;
		// Get count down and erase sequences.
		for (auto& item : m_effect_sequences.at(id)) {
			item->Disable();
		}
		m_effect_sequences.erase(id);
	}
	else {
		// Do something.
	}
}

void PostProcessingManager::Render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_effects.at("__df__")->RenderEffect();
}

};