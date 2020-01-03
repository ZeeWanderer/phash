// phash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "PerfectHash.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

using namespace std::string_literals;

typedef std::vector<bool> hash_bin;

// Use delete[] on retuned image pointer
std::tuple<stbi_uc*, int, int, int> GetGrayImage(const std::filesystem::path file, int r_width = 8, int r_height = 8)
{

	int width, height, channels;
	auto image = stbi_load(file.string().c_str(), &width, &height, &channels, 0);

	const int g_width = r_width, g_height = r_height, r_channels = channels, g_channels = 1;

	stbi_uc* resized_img = new stbi_uc[(size_t)r_width * r_height * r_channels];

	stbi_uc* gray_img = new stbi_uc[(size_t)g_width * g_height * g_channels];

	stbir_resize_uint8(image, width, height, 0, resized_img, r_width, r_height, 0, r_channels);

	size_t r_img_size = (size_t)r_width * r_height * r_channels;

	for (unsigned char* p = resized_img, *pg = gray_img; p != resized_img + r_img_size; p += channels, pg += g_channels)
	{
		//auto tmp0 = p[0] * 0.298839;
		//auto tmp1 = p[1] * 0.586811;
		//auto tmp2 = p[2] * 0.11435;
		//auto tmp = tmp0 + tmp1 + tmp2;
		*pg = (uint8_t)round(p[0] * 0.298839 + p[1] * 0.586811 + p[2] * 0.11435);
	}

	stbi_image_free(image);

	delete[] resized_img;

	return { gray_img, g_width, g_height, g_channels };
}

int SaveImage(const std::filesystem::path file, stbi_uc* image, int width, int height, int channels)
{
	auto tmp = file.parent_path();
	std::filesystem::create_directories(file.parent_path());
	auto ret = stbi_write_jpg(file.string().c_str(), width, height, channels, image, 100);
	return ret;
}

std::string GetHashString(const std::vector<bool>& v)
{
	std::string retval;
	retval.reserve(v.size());

	for (auto b : v)
	{
		if (b)
			retval.push_back('1');
		else
			retval.push_back('0');
	}
	return retval;
}

std::string HashBinToHex(const std::string& hash)
{
	//TODO: avoid duplication. Use same buffer as a source and destination

	auto size = hash.size();
	const auto tmp = size % 4;
	const auto offset = 4 - tmp;
	if (tmp != 0)
	{
		size += offset;
	}

	char* const retval = new char[size];

	char* out = retval;

	if (tmp != 0)
	{
		for (size_t idx = 0; idx < offset; idx++)
		{
			*out++ = '0';
		}
	}

	for (size_t idx = 0; idx < hash.size(); idx++)
	{
		*out++ = hash.at(idx);
	}

	out = retval;
	for (auto it = retval; it < retval + size; it += 4)
		*out++ = Perfect_Hash::hexchar(it);

	std::string ret_str(retval, size / 4);
	delete[] retval;
	return ret_str;
}

int SaveHashFile(const std::filesystem::path image_file, const std::string hash_string, const std::string hesh_hex_string)
{
	auto out_hex_file = image_file;
	out_hex_file.replace_extension("hash");

	std::filesystem::create_directories(out_hex_file.parent_path());
	std::ofstream out_hash(out_hex_file.c_str());
	out_hash << hash_string << std::endl << hesh_hex_string;
	return 0;
}

int SaveDuplicatesFile(const std::filesystem::path duplicates_file, const std::vector<bool> b_is_duplicate, const std::vector<std::filesystem::path> duplicate_files, const bool bOutputToCMD = false)
{
#ifdef __TRACE
	std::cout << "SaveDuplicatesFile :" << std::endl;
#endif
	if(!bOutputToCMD)
	{
		auto out_dup_file = duplicates_file;
		out_dup_file.replace_extension("dup");

		std::filesystem::create_directories(out_dup_file.parent_path());
		std::ofstream out_hash(out_dup_file.c_str());
#ifdef __TRACE
		std::cout << "out_hash.is_open() :" << out_hash.is_open() << std::endl;
#endif
		for (size_t idx = 0; idx < b_is_duplicate.size(); idx++)
		{
			if (b_is_duplicate[idx])
			{
#ifdef __TRACE
				std::cout << "duplicate_files[idx].string().c_str() :" << duplicate_files[idx].string().c_str() << std::endl;
#endif
				out_hash << duplicate_files[idx].string().c_str() << std::endl;

			}
		}
		out_hash.close();
	}
	else
	{
		for (size_t idx = 0; idx < b_is_duplicate.size(); idx++)
		{
			if (b_is_duplicate[idx])
			{
#ifdef __TRACE
				std::cout << "duplicate_files[idx].string().c_str() :" << duplicate_files[idx].string().c_str() << std::endl;
#endif
				std::cout << duplicate_files[idx].string().c_str();
				if(idx < b_is_duplicate.size()-1)
					std::cout << "|";

			}
		}
	}
	
	return 0;
}

struct phOutPathData
{
	std::filesystem::path output_path;
	std::filesystem::path input_path;
	std::string FLAGS_hash;
	int hash_width;
	int hash_height;
};

std::filesystem::path GetOutputPath(phOutPathData& p)
{
	using namespace std::filesystem;
	//TODO: get difference in path to exec dir and get all path except top dir
	//TODO: replace with proper concatenation
	const auto filename = p.input_path.filename();
	const auto input_path_r = relative(p.input_path).remove_filename();

	auto output_p = relative(p.output_path);

	for (auto it = ++input_path_r.begin(); it != input_path_r.end(); ++it)
	{
		output_p /= *it;
	}
	
	output_p /= path{ p.FLAGS_hash } / path{ ("r_"s + std::to_string(p.hash_width) + "x"s + std::to_string(p.hash_height)) } / filename;
	return output_p;
}

std::string GetHashFromFile(const std::filesystem::path image_file, const bool bGetBin = true)
{
	auto in_hash_file = image_file;
	in_hash_file.replace_extension("hash");

	std::ifstream in_hash(in_hash_file.c_str());
	std::string hash_str;

	std::getline(in_hash, hash_str);
	//if (bGetBin)
	//{
	//	std::getline(in_hash, hash_str);
	//}
	//else
	//{

	//}
	return hash_str;
}

hash_bin GetSimpleHash(stbi_uc* image, int width, int height, int channels)
{
	// Simpe Hash
	size_t summ = 0;
	const size_t size = (size_t)width * height * channels;

	for (size_t idx = 0; idx < size; idx++)
	{
		summ += image[idx];
	}
	uint8_t mean = summ / size;

	hash_bin hash(size);

	for (size_t idx = 0; idx < size; idx++)
	{
		const auto tmp = image[idx];
		if (tmp < mean)
		{
			hash[idx] = false;
		}
		else
		{
			hash[idx] = true;
		}
	}

	return hash;
}

hash_bin GetMedianHash(stbi_uc* image, int width, int height, int channels)
{
	size_t summ = 0;
	const size_t size = (size_t)width * height * channels;

	stbi_uc* sorted = new stbi_uc[size];
	memcpy_s(sorted, size, image, size);
	std::sort(sorted, sorted + size);

	uint8_t median = 0;

	if (size % 2 == 0)
	{
		median = (sorted[size / 2] + sorted[size / 2 - 1]) / 2;
	}
	else
	{
		median = sorted[size / 2];
	}
	delete[] sorted;

	hash_bin hash(size);

	for (size_t idx = 0; idx < size; idx++)
	{
		const auto tmp = image[idx];
		if (tmp < median)
		{
			hash[idx] = false;
		}
		else
		{
			hash[idx] = true;
		}
	}

	return hash;
}

hash_bin GetDiffHash(stbi_uc* image, int width, int height, int channels)
{
	size_t summ = 0;
	const size_t size = (size_t)width * height * channels;
	const size_t diff_size = (size_t)(width-1) * height * channels;

	int16_t* difference = new int16_t[diff_size];

	for (size_t idx0 = 0; idx0 < height; idx0++)
	{
		for (size_t idx1 = 0; idx1 < width - 1; idx1++)
		{
			difference[idx0 * (width - 1) + idx1] = (int16_t)image[idx0 * width + idx1 + 1] - image[idx0 * width + idx1];
		}
	}

	hash_bin hash(diff_size);


	for (size_t idx = 0; idx < diff_size; idx++)
	{
		if (difference[idx] <= 0)
		{
			hash[idx] = 0;
		}
		else
		{
			hash[idx] = 1;
		}
	}

	delete[] difference;
	return hash;
}

hash_bin GetCosineHash(stbi_uc* image, int width, int height, int channels)
{
	const size_t size = (size_t)width * height * channels;	

	auto b_width = width / 4;
	auto b_height = height / 4;

	const size_t b_size = (size_t)b_width * b_height * channels;
	hash_bin hash(b_size);

	double* b_dct_arr = new double[b_size];
	memset(b_dct_arr, 0, b_size * sizeof(*b_dct_arr));

	double alpha_u = sqrt(2.0 / (double)width);
	double alpha_v = sqrt(2.0 / (double)height);

	for (size_t idx_v = 0; idx_v < b_height; idx_v++)
	{
		const auto real_idx_v = (idx_v + 1);
		for (size_t idx_u = 0; idx_u < b_width; idx_u++)
		{
			const auto real_idx_u = (idx_u + 1);
			///////////////////
			for (size_t idx_y = 0; idx_y < height; idx_y++)
			{
				for (size_t idx_x = 0; idx_x < width; idx_x++)
				{
					b_dct_arr[idx_v * b_width + idx_u] += alpha_u * alpha_v * (double)image[idx_y * width + idx_x] * cos((double)((2 * idx_x + 1) * real_idx_u) * M_PI / (2.0 * (double)width)) * cos((double)((2 * idx_y + 1) * real_idx_v) * M_PI / (2.0 * (double)height));
				}
			}
		}
	}

	double summ = 0;

	for (size_t idx = 0; idx < b_size; idx++)
	{
		summ += b_dct_arr[idx];
	}
	double mean = summ / (double)b_size;

	for (size_t idx = 0; idx < b_size; idx++)
	{
		const auto tmp = b_dct_arr[idx];
		if (tmp < mean)
		{
			hash[idx] = false;
		}
		else
		{
			hash[idx] = true;
		}
	}

	delete[] b_dct_arr;
	return hash;
}

enum class HashType : int
{
	Unknown,
	SimpleHash,
	MedianHash,
	DiffHash,
	CosineHash
};

enum class ErrorType : int
{
	Unknown,
	BER,
	MER
};

ErrorType GetErrorTypeFromString(const std::string& type)
{
	if (type == "ber")
		return ErrorType::BER;
	if (type == "mer")
		return ErrorType::MER;

	return ErrorType::Unknown;
}

const std::map<HashType, std::tuple<int, int>> hash_image_sizes
{
	{HashType::SimpleHash, {32, 32}},
	{HashType::MedianHash, {32, 32}},
	{HashType::CosineHash, {8, 8}},
	{HashType::DiffHash, {33, 32}} // (K+1)xK
};

typedef std::function<hash_bin(stbi_uc * image, int width, int height, int channels)> Hash_func;

typedef std::function<std::tuple<int,int>(int base)> Hash_resolution_func;

const std::map<HashType, Hash_func> hash_functions
{
	{HashType::SimpleHash, GetSimpleHash},
	{HashType::MedianHash, GetMedianHash},
	{HashType::DiffHash, GetDiffHash},
	{HashType::CosineHash, GetCosineHash}
};

const std::tuple<int, int> GetHashResolution(const int base, const HashType type)
{
	switch (type)
	{
	case HashType::SimpleHash:
	case HashType::MedianHash:
	case HashType::CosineHash:
		return {base, base};
	case HashType::DiffHash:
		return {base + 1, base};
	default:
		return { 0, 0 };
	}
}

HashType GetHashTypeFromString(const std::string& type)
{
	if (type == "simple")
		return HashType::SimpleHash;
	if (type == "median")
		return HashType::MedianHash;
	if (type == "diff")
		return HashType::DiffHash;
	if (type == "cosine")
		return HashType::CosineHash;

	return HashType::Unknown;
}


int main(int argc, char** argv)
{
	argparse::ArgumentParser program("phash");

	program.add_argument("-i", "--input")
		.required()
		.help("Specify single input image file or directory");

	program.add_argument("-o", "--output")
		.required()
		.help("Specify output directory");

	program.add_argument("-d", "--duplicates")
		.help("Specify single input image file to searh for duplicates in input directory");

	program.add_argument("-h", "--hash")
		.required()
		.help("Specify one hash type from [simple, median, diff, cosine]")
		.action([](const std::string& value) 
			{
				static const std::vector<std::string> choices = { "simple", "median", "diff", "cosine" };
				if (std::find(choices.begin(), choices.end(), value) != choices.end()) 
				{
					return value;
				}
				throw std::runtime_error("Invalid hash: "s + value);
			});

	program.add_argument("-et","--error_type")
		.required()
		.help("Specify one error type from [ber, mer]")
		.action([](const std::string& value)
			{
				static const std::vector<std::string> choices = {"ber", "mer"};
				if (std::find(choices.begin(), choices.end(), value) != choices.end())
				{
					return value;
				}
				throw std::runtime_error("Invalid hash: "s + value);
			});

	program.add_argument("-r","--resolution")
		.help("Specify resolution base")
		.default_value(0)
		.action([](const std::string& value) 
			{	int retval;
				std::from_chars(value.c_str(), value.c_str() + value.size(), retval);
				return retval; 
			});

	program.add_argument("-e", "--error")
		.help("supply error rate (0...1], default is 0.17")
		.default_value(0.17)
		.action([](const std::string& value) 
			{	double retval;
				std::from_chars(value.c_str(), value.c_str() + value.size(), retval);
				return retval; 
			});

	program.add_argument("--save")
		.help("save resized grayscale images")
		.default_value(false)
		.implicit_value(true);

	program.add_argument("--force")
		.help("froce rehash of all files")
		.default_value(false)
		.implicit_value(true);

	program.add_argument("--get_path")
		.help("output path to dup file for given parameters")
		.default_value(false)
		.implicit_value(true);

	program.add_argument("-p", "--profile")
		.help("output hash time")
		.default_value(false)
		.implicit_value(true);

	program.add_argument("--out_cmd")
		.help("output duplicates to console instead of file")
		.default_value(false)
		.implicit_value(true);

	try
	{
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error & err) {
		std::cout << err.what() << std::endl;
		std::cout << program;
		exit(0);
	}

	auto FLAGS_multiple = false;
	auto FLAGS_resolution = program.get<int>("--resolution");
	auto FLAGS_save_gray = program.get<bool>("--save");
	auto FLAGS_force = program.get<bool>("--force");
	auto FLAGS_profile = program.get<bool>("--profile");
	auto FLAGS_input_path = program.get<std::string>("--input");
	auto FLAGS_output_path = program.get<std::string>("--output");
	auto FLAGS_hash = program.get<std::string>("--hash");
	auto FLAGS_error_type = program.get<std::string>("--error_type");
	auto FLAGS_error = program.get<double>("--error");

	auto FLAGS_get_path = program.get<bool>("--get_path");

	auto FLAGS_out_cmd = program.get<bool>("--out_cmd");

	std::string FLAGS_base_for_duplicates_path;
	bool bSearchForDuplicates = false;
	try
	{
		FLAGS_base_for_duplicates_path = program.get<std::string>("--duplicates");
		bSearchForDuplicates = true;
	}
	catch(...){ }


	const std::filesystem::path input_path{ FLAGS_input_path };
	const std::filesystem::path output_path{ FLAGS_output_path };
	const std::filesystem::path base_for_duplicates_path{ FLAGS_base_for_duplicates_path };



	if (bSearchForDuplicates)
	{
		if (!std::filesystem::is_regular_file(base_for_duplicates_path))
		{
			std::cout << "Invalid d file: " << base_for_duplicates_path;
			exit(0);
		}
	}

	if (!std::filesystem::exists(output_path))
	{
		auto res = std::filesystem::create_directories(output_path);
		if (!res)
		{
			std::cout << "Invalid output directory: " << output_path;
			exit(0);
		}
	}

	//TODO: simplify
	if (!std::filesystem::is_regular_file(input_path))
	{
		if (std::filesystem::is_directory(input_path))
		{
			FLAGS_multiple = true;
		}
		else
		{
			std::cout << "Input is not a file or directory" << std::endl;
			return 1;
		}
	}

	// TODO: handle MER in hex
	const auto error_type = GetErrorTypeFromString(FLAGS_error_type);

	const auto hash_type = GetHashTypeFromString(FLAGS_hash);
	if (hash_type == HashType::Unknown)
	{
		std::cout << "Invalid hash method" << std::endl;
		return 2;
	}

	// Define in loop shared parameters
	int hash_width, hash_height;

	if (FLAGS_resolution)
	{
		const auto [tmp_width, tmp_height] = GetHashResolution(FLAGS_resolution, hash_type);
		hash_width = tmp_width;
		hash_height = tmp_height;
	}
	else
	{
		const auto [tmp_width, tmp_height] = hash_image_sizes.at(hash_type);
		hash_width = tmp_width;
		hash_height = tmp_height;
	}

	if (FLAGS_get_path)
	{

		phOutPathData p;
		p.FLAGS_hash = FLAGS_hash;
		p.input_path = base_for_duplicates_path;
		p.output_path = output_path;
		p.hash_height = hash_height;
		p.hash_width = hash_width;

		auto output_duplicates_file = GetOutputPath(p);

		std::cout << output_duplicates_file.string();
		return 0;
	}

#ifdef __TRACE
	////////////////////////////////////////
	std::cout << FLAGS_error << std::endl;
#endif

	std::vector<std::filesystem::path> input_files;


	//TODO: simplify
	if (FLAGS_multiple)
	{
		for (auto& p : std::filesystem::recursive_directory_iterator(FLAGS_input_path))
		{
			if (p.is_regular_file())
			{
				input_files.emplace_back(p);
			}
		}
	}
	else
	{
		input_files.emplace_back(input_path);
	}

	std::chrono::steady_clock::time_point start;
	if (FLAGS_profile)
		start = std::chrono::steady_clock::now();

	///////////////////////
	// GET HASHES

	// TODO: do not compute hashes if they ixesit or are up to date 
	std::vector<std::filesystem::path> to_hash_files;

	if (FLAGS_force)
	{
		to_hash_files = input_files;
	}
	else
	{
		to_hash_files.reserve(input_files.size());
		phOutPathData p;
		p.FLAGS_hash = FLAGS_hash;
		p.output_path = output_path;
		p.hash_height = hash_height;
		p.hash_width = hash_width;

		for (int idx = 0; idx < input_files.size(); idx++)
		{
			const auto input_file = input_files[idx];
			p.input_path = input_file;
			auto output_file = GetOutputPath(p);

			auto hash_file = output_file.parent_path() / output_file.filename().replace_extension("hash");

			if (!std::filesystem::is_regular_file(hash_file))
			{
				to_hash_files.emplace_back(input_file);
			}
			
		}
	}

	const auto hash_function = hash_functions.at(hash_type);

#pragma omp parallel for
	for (int idx = 0; idx < to_hash_files.size(); idx++)
	{
		const auto input_file = to_hash_files[idx];

		auto l_hash_width = hash_width;
		auto l_hash_height = hash_height;

		phOutPathData p;
		p.FLAGS_hash = FLAGS_hash;
		p.input_path = input_file;
		p.output_path = output_path;
		p.hash_height = l_hash_height;
		p.hash_width = l_hash_width;

		auto output_file = GetOutputPath(p);

		// cosine special case
		if (hash_type == HashType::CosineHash)
		{
			l_hash_width = l_hash_width * 4;
			l_hash_height = l_hash_height * 4;
		}

		const auto [gray_image, width, height, channels] = GetGrayImage(input_file, l_hash_width, l_hash_height);

		if (FLAGS_save_gray)
			SaveImage(output_file, gray_image, width, height, channels);

		const auto hash = hash_function(gray_image, l_hash_width, l_hash_height, channels);

		// cosine special case
		if (hash_type == HashType::CosineHash)
		{
			l_hash_width = l_hash_width / 4;
			l_hash_height = l_hash_height / 4;
		}

		const auto hash_string = GetHashString(hash);
		const auto hesh_hex_string = HashBinToHex(hash_string);

		SaveHashFile(output_file, hash_string, hesh_hex_string);

		delete[] gray_image;
	}

	if (FLAGS_profile)
	{
		auto end = std::chrono::steady_clock::now();
		auto duration = end - start;
		std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(duration).count() << " sec\n";
	}

	///////////////////////
	// FIND DUPLICATES
	if (bSearchForDuplicates)
	{
		std::vector<std::filesystem::path> files_to_check_for_duplicates = input_files;

		// TODO: REMAKE PROPERLY

		//Exclude base duplicate file
		auto it = std::find(files_to_check_for_duplicates.begin(), files_to_check_for_duplicates.end(), base_for_duplicates_path);
		files_to_check_for_duplicates.erase(it);

		// Flags vector, for #pragma omp parallel for
		std::vector<bool> b_is_duplicate_files(files_to_check_for_duplicates.size());

		phOutPathData p;
		p.FLAGS_hash = FLAGS_hash;
		p.input_path = base_for_duplicates_path;
		p.output_path = output_path;
		p.hash_height = hash_height;
		p.hash_width = hash_width;

		auto output_duplicates_file = GetOutputPath(p);

		auto base_hash = GetHashFromFile(output_duplicates_file);


#pragma omp parallel for
		for (int idx = 0; idx < files_to_check_for_duplicates.size(); idx++)
		{
			const auto input_file = files_to_check_for_duplicates[idx];

			phOutPathData p;
			p.FLAGS_hash = FLAGS_hash;
			p.input_path = input_file;
			p.output_path = output_path;
			p.hash_height = hash_height;
			p.hash_width = hash_width;

#ifdef __TRACE
			std::cout << "input_file :" << input_file << std::endl;
#endif

			auto output_file = GetOutputPath(p);

#ifdef __TRACE
			std::cout << "output_file :" << output_file << std::endl;
#endif

			auto curr_hash = GetHashFromFile(output_file);
#ifdef __TRACE
			std::cout << "curr_hash :" << curr_hash << std::endl;
#endif
			auto base_n = curr_hash.size();

			auto errors = 0;

			auto error_rate = 0.0;

			for (auto idx = 0ull; idx < base_n; idx++)
			{
				if (base_hash[idx] != curr_hash[idx])
				{
					errors++;
				}
			}

#ifdef __TRACE
			std::cout << "errors :" << errors << std::endl;
#endif

			switch (error_type)
			{
			case ErrorType::BER:
				error_rate = static_cast<double>(errors) / static_cast<double>(base_n);
				break;
			case ErrorType::MER:
				error_rate = static_cast<double>(errors) / static_cast<double>(base_n);
				break;
			default:
				break;
			}

#ifdef __TRACE
			std::cout << "error_rate :" << error_rate << std::endl;
#endif
			
			if (error_rate <= FLAGS_error)
			{
				
				b_is_duplicate_files[idx] = true;
			}

#ifdef __TRACE
			std::cout << "is duplicate :" << (error_rate <= FLAGS_error) << std::endl;
			std::cout << std::endl;
#endif
		}

		SaveDuplicatesFile(output_duplicates_file, b_is_duplicate_files, files_to_check_for_duplicates, FLAGS_out_cmd);
	}


	return 0;
}

