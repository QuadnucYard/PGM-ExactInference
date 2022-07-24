#include "CLI11.hpp"
#include "CBNSumProduct.h"
#include "CliqueTreeMethod.h"
#include "CommonIO.h"
#include "clihelper.h"
#include <iostream>

int main(int argc, char** argv) {
	CLI::App app {"Welcome to PGM Exact Inference by QuadnucYard!"};

	std::filesystem::path fnroot, fnin, fnout, fnquery = "Query.yaml";
	bool useSP = true, useCT = true;
	app.add_flag("--sp", useSP, "Use SumProduct Method");
	app.add_flag("--ct", useSP, "Use CliqueTree Method");
	app.add_option("-r", fnroot, "Root path");
	app.add_option("-i", fnin, "Input file")->required();
	app.add_option("-q", fnquery, "Query file")->required();
	app.add_option("-o", fnout, "Output file");

	CLI11_PARSE(app, argc, argv);

	std::cout << app.get_description() << std::endl;

	if (useSP) {
		try {
			msg("Infer with BNSumProduct Method...");
			pgm::io::readQuery(fnroot / fnin);
			pgm::CBNSumProduct theBN(pgm::io::readBayesianNetwork(fnroot / fnin));
			msg("Finished reading BN structure and parameters.");
			auto queries = pgm::io::readQuery(fnroot / fnquery);
			auto result = theBN.query(queries);
			msg("Query results:");
			msg(pgm::io::toResultString(result).c_str());
		} catch (std::exception e) {
			msgerr(e.what());
		}
	}
	if (useCT) {
		try {
			msg("Infer with CliqueTree Method...");
			pgm::io::readQuery(fnroot / fnin);
			pgm::CliqueTreeMethod theCT(pgm::io::readCliqueTree(fnroot / "CliqueTree.yaml"));
			msg("Finished reading CT structure and parameters.");
			auto queries = pgm::io::readQuery(fnroot / fnquery);
			auto result = theCT.query(queries);
			msg("Query results:");
			msg(pgm::io::toResultString(result).c_str());
		} catch (std::exception e) {
			msgerr(e.what());
		}
	}

	return 0;
}