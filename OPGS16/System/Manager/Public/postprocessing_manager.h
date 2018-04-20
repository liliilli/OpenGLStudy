#ifndef OPGS16_S_SYSTEM_SHADER_POST_PROCESSING_MANAGER_H
#define OPGS16_S_SYSTEM_SHADER_POST_PROCESSING_MANAGER_H

/*!---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*
 * @license BSD 2-Clause License
 *
 * Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
 * If you want to read full statements, read LICENSE file.
 *----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*/

/*!---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*
 * @file System/Manager/Public/postprocessing_manager.h
 * @brief Elementary manager class to manage post-processing shaders.
 *
 * This file consists of application operation class and member API functions.
 *
 * @author Jongmin Yun
 * @log
 * 2018-02-18 Create file.
 * 2018-03-04 Refactoring. Move class to /Manager class.
 * 2018-04-20 Refactoring. CPostProcessingFrame to ::opgs16::element::CPostProcessingFrame.
 *----*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*/

#include <memory>
#include <string>
#include <unordered_map>
#include "../../Shader/pp_frame.h"

namespace opgs16 {
namespace manager {

/**
 * @class MPostProcessingManager
 * @brief This class manages post-processing frame (instances) to be used in Application.
 * Each post-processing instance stored in container could be attached, released, destroyed in
 * any time but Strongly recommends it in Initiate time and Update time.
 */
class MPostProcessingManager final {
public:
	using pp_effect = std::unique_ptr<element::CPostProcessingFrame>; // Abbreviation.
	using ppf_ptr	= element::CPostProcessingFrame*;
	using sequence_type = std::list<ppf_ptr>;

public:
	/**
	 * @brief Static method gets unique instance of PostProcessingManager class.
	 * @return Lvalue reference of singleton instance.
	 */
	static MPostProcessingManager& GetInstance() {
		static MPostProcessingManager instance{};
		return instance;
	}

	/**
	 * @brief Get lvalue reference of effect which is named with tag.
	 * @param[in] tag
	 * @return Lvalue reference of effect.
	 */
	pp_effect& GetEffect(const std::string&& tag);

	/**
	 * @brief Insert effect (vacant) instance into effect container.
	 * Type paramter must be written in <> and which must derive PostProcessingFrame base class.
	 *
	 * @param[in] tag tag The tag to use.
	 * @param[in] _Ty Post-processing Effect type parameter to use.
	 * @return If this method success to create and insert _Ty effect, return True.
	 */
	template <class _Ty, typename = std::enable_if_t<std::is_base_of_v<element::CPostProcessingFrame, _Ty>>>
	bool InsertEffect(const char* tag) {
		if (IsEffectExist(tag)) { return false; }

		m_effects[tag] = std::make_unique<_Ty>();
		return true;
	}

	/** Overloading version of InsertEffect<_Ty, ...>(tag) */
	bool InsertEffect(const char* tag);

	/**
	 * @brief Insert effect and initiate automatically.
	 * Type paramter must be written in <> and which must derive PostProcessingFrame base class.
	 *
	 * @param[in] tag tag The tag to use.
	 * @param[in] _Ty Post-processing Effect type parameter to use.
	 * @return If this method success to create and insert _Ty effect, return True.
	 */
	template <class _Ty, typename = std::enable_if_t<std::is_base_of_v<element::CPostProcessingFrame, _Ty>>>
	bool InsertEffectInitiate(const char* tag) {
		if (InsertEffect<_Ty>(tag)) {
			m_effects[tag]->Initialize();
			return true;
		}
		else return false;
	}

	/**
	 * @brief Find whether or not effect named tag is exist.
	 * @param[in] tag The tag to find effect.
	 * @return If searching effect is successful, return true. else return false.
	 */
	bool IsEffectExist(const std::string& tag) {
        return m_effects.find(tag) != m_effects.end();
	}

	/**
	 * @brief Set continous post-processing sequence to render screen.
	 * If sequence list on id is already set up, This method does nothing.
	 *
	 * @param[in] id Id which is position to be set effect sequences.
	 * @param[in] list Effect tags list
	 * @return Pointer of initialized effect sequence.
	 * If this fails to create sequence, return nullptr.
	 */
	const sequence_type* SetSequence(const size_t id, const std::initializer_list<std::string>& list);

	/**
	 * @brief Updates each effects of each sequences. (each effects of sequence is active)
	 */
	void UpdateSequences();

	/**
	 * @brief Bind effect sequence with id number.
	 * @param[in] id Index position of effect sequences container to bind seqeunce.
	 */
	void BindSequence(const size_t id);

	/**
	 * @brief
	 */
	void Render();

	/**
	 * @brief
	 * #param[in] list
	 */
	void ReleaseSequence(const size_t id);

private:
	/** Container sotres post-processing separated effects. */
	std::unordered_map<std::string, pp_effect> m_effects;
	/** Container stores post-processing sequences combined with effects. */
	std::unordered_map<size_t, sequence_type> m_effect_sequences;

	const size_t m_reset = 0xffff;				// Just used for reset of m_binded_number
	mutable size_t m_binded_number{m_reset};	// if not reset, call effect sequence via this

	/** Return id'th position of effect_sequences is already exist. */
	bool DoesEffectSequenceExist(const size_t id) {
        return m_effect_sequences.find(id) != m_effect_sequences.end();
	}

	MPostProcessingManager();

public:
    MPostProcessingManager(const MPostProcessingManager&) = delete;
    MPostProcessingManager& operator=(const MPostProcessingManager&) = delete;
};

} /*! opgs16::manager */
} /*! opgs16 */

#endif /** OPGS16_S_SYSTEM_SHADER_POST_PROCESSING_MANAGER_H */
