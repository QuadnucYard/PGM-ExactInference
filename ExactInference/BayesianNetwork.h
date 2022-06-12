#pragma once
#include "factordef.h"
#include "qyranges.hpp"

namespace pgm {

	class BayesianNetwork {

	public:
		struct Node {
			fid_t id;
			fidlist parents;	//�����id
			fvallist cptvals;	//CPT��ֵ
		};

		VariableList variables;		//������
		std::vector<Node> nodes;	//����б�

	public:
		inline const Variable& getVar(fid_t id) const {
			return *std::ranges::find(variables, id, &Variable::id);
		}
	};

	namespace io {
		//��ȡ��Ҷ˹����ṹ�Ͳ���
		BayesianNetwork readBayesianNetwork(const std::string& filename);
	}
}