#pragma once
#include <array>
#include <algorithm>
#include <cassert>
#include <string>


class Perfect_Hash {
private:
	static constexpr unsigned char asso_values[] = {
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 15, 7,  3,  1,  0,  27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
		27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27 };
	template <typename It>
	static constexpr unsigned int hash(It str)
	{
		return
			asso_values[(unsigned char)str[3] + 2] + asso_values[(unsigned char)str[2] + 1] +
			asso_values[(unsigned char)str[1] + 3] + asso_values[(unsigned char)str[0]];
}

	static constexpr char hex_lut[] = "???????????fbead9c873625140";
public:
#ifdef DEBUG
	template <typename It>
	static char hexchar(It binary_nibble)
	{
		assert(Perfect_Hash::validate(binary_nibble)); // for DEBUG only
		return hex_lut[hash(binary_nibble)]; // no validation!
	}
#else
	template <typename It>
	static constexpr char hexchar(It binary_nibble)
	{
		return hex_lut[hash(binary_nibble)]; // no validation!
	}
#endif
	template <typename It>
	static bool validate(It str)
	{
		static constexpr std::array<char, 4> vocab[] = {
			{{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
			{{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
			{{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
			{{'?', '?', '?', '?'}}, {{'?', '?', '?', '?'}},
			{{'1', '1', '1', '1'}}, {{'1', '0', '1', '1'}},
			{{'1', '1', '1', '0'}}, {{'1', '0', '1', '0'}},
			{{'1', '1', '0', '1'}}, {{'1', '0', '0', '1'}},
			{{'1', '1', '0', '0'}}, {{'1', '0', '0', '0'}},
			{{'0', '1', '1', '1'}}, {{'0', '0', '1', '1'}},
			{{'0', '1', '1', '0'}}, {{'0', '0', '1', '0'}},
			{{'0', '1', '0', '1'}}, {{'0', '0', '0', '1'}},
			{{'0', '1', '0', '0'}}, {{'0', '0', '0', '0'}},
		};
		int key = hash(str);

		if (key <= 26 && key >= 0)
			return std::equal(str, str + 4, vocab[key].begin());
		else
			return false;
	}
};

constexpr unsigned char Perfect_Hash::asso_values[];
constexpr char Perfect_Hash::hex_lut[];
