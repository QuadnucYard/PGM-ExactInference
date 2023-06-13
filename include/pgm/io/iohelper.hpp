#pragma once
#include <filesystem>
#include <ryml/ryml.hpp>
#include <ryml/ryml_std.hpp>

namespace pgm::io {

	template <class CharContainer>
	inline CharContainer file_get_contents(const char* filename);

	template <class CharContainer>
	inline size_t file_get_contents(const char* filename, CharContainer* v);

	template <class CharContainer>
	inline void file_put_contents(const char* filename, CharContainer const& v,
								  const char* access = "wb");

	inline void file_put_contents(const char* filename, const char* buf, size_t sz,
								  const char* access);

	template <class CharContainer>
	size_t file_get_contents(const char* filename, CharContainer* v) {
		::FILE* fp = ::fopen(filename, "rb");
		C4_CHECK_MSG(fp != nullptr, "could not open file");
		::fseek(fp, 0, SEEK_END);
		long sz = ::ftell(fp);
		v->resize(static_cast<typename CharContainer::size_type>(sz));
		if (sz) {
			::rewind(fp);
			size_t ret = ::fread(&(*v)[0], 1, v->size(), fp);
			C4_CHECK(ret == (size_t)sz);
		}
		::fclose(fp);
		return v->size();
	}

	/** load a file from disk into an existing CharContainer */
	template <class CharContainer>
	CharContainer file_get_contents(const char* filename) {
		CharContainer cc;
		file_get_contents(filename, &cc);
		return cc;
	}

	/** save a buffer into a file */
	template <class CharContainer>
	void file_put_contents(const char* filename, CharContainer const& v, const char* access) {
		file_put_contents(filename, v.empty() ? "" : &v[0], v.size(), access);
	}

	/** save a buffer into a file */
	void file_put_contents(const char* filename, const char* buf, size_t sz, const char* access) {
		::FILE* fp = ::fopen(filename, access);
		C4_CHECK_MSG(fp != nullptr, "could not open file");
		::fwrite(buf, 1, sz, fp);
		::fclose(fp);
	}

	inline ryml::Tree parse_yaml(const char* filename) {
		std::string contents = file_get_contents<std::string>(filename);
		return ryml::parse_in_arena(ryml::to_csubstr(contents));
	}

} // namespace pgm::io