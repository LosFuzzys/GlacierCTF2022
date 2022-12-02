#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <x86intrin.h>
#include <wmmintrin.h>
#include "base64.h"

// https://gist.github.com/acapola/d5b940da024080dfaf5f

#define HASH_SIZE 44
#define SINGLE_BUFFER_SIZE 4096

#define AES_128_key_exp(k, rcon) aes_128_key_expansion(k, _mm_aeskeygenassist_si128(k, rcon))

__m128i key_schedule[10];


__m128i aes_128_key_expansion(__m128i key, __m128i keygened){
	keygened = _mm_shuffle_epi32(keygened, _MM_SHUFFLE(3,3,3,3));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	return _mm_xor_si128(key, keygened);
}

//public API
void aes128_load_key(int8_t *enc_key){
    key_schedule[0] = _mm_loadu_si128((const __m128i*) enc_key);
	key_schedule[1]  = AES_128_key_exp(key_schedule[0], 0x01);
	key_schedule[2]  = AES_128_key_exp(key_schedule[1], 0x02);
	key_schedule[3]  = AES_128_key_exp(key_schedule[2], 0x04);
	key_schedule[4]  = AES_128_key_exp(key_schedule[3], 0x08);
	key_schedule[5]  = AES_128_key_exp(key_schedule[4], 0x10);
	key_schedule[6]  = AES_128_key_exp(key_schedule[5], 0x20);
	key_schedule[7]  = AES_128_key_exp(key_schedule[6], 0x40);
	key_schedule[8]  = AES_128_key_exp(key_schedule[7], 0x80);
	key_schedule[9]  = AES_128_key_exp(key_schedule[8], 0x1B);
	key_schedule[10] = AES_128_key_exp(key_schedule[9], 0x36);

}

void enc_aes(char* input, char* output)
{
	__m128i m = _mm_loadu_si128((__m128i *) input);
	m = _mm_xor_si128       (m, key_schedule[ 0]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 1]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 2]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 3]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 4]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 5]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 6]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 7]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 8]); \
	m = _mm_aesenc_si128    (m, key_schedule[ 9]); \
	m = _mm_aesenclast_si128(m, key_schedule[10]);\
	_mm_storeu_si128((__m128i *) output, m);
}

// looks complicated, but is just static XOR + AES
char* hash_avx(char* input)
{
	
	char mask_b[32] = {0x1, 0x35, 0xa7, 0x73, 0x3f, 0x55, 0x57, 0xc1, 0xa9, 0xac, 0x73, 0xf8, 0x9, 0x95, 0x9c, 0xe1, 0x2e, 0xa, 0x70, 0xe3, 0xc2, 0x5b, 0x69, 0xbb, 0xc, 0x39, 0xca, 0xbb, 0x31, 0x2, 0x2c, 0xc9};
 	__m256 inp = _mm256_loadu_ps((float*) input);
	__m256 mask = _mm256_loadu_ps((float*) mask_b);
	__m256 out8 = _mm256_xor_ps(inp, mask);
	char out[32];
	_mm256_storeu_ps((float*)out, out8);

	char key[16] = {0xec, 0x12, 0xd, 0x58, 0x47, 0x9, 0xc7, 0xca, 0x50, 0xe5, 0x7d, 0x8, 0x4f, 0x59, 0x28, 0xf4};
	
	char final[32];
	aes128_load_key(key);
	enc_aes(out, final);
	enc_aes(&out[16], &final[16]);
	int output_len;
	return base64(final, 32, &output_len);


}


int checkPassword(char* hash)
{
	char* password = calloc(33, 1);
	printf("Password: ");
	scanf("\n%32[^\n]", password);
	// temporary testing code

	char* pass = hash_avx(password);
	if(strcmp(pass, hash))
	{
		printf("%s != %s\n", password, hash);
		exit(-1);
	}
	
}

char* read_userlist()
{
	int fd = open("./userlist.txt", O_RDONLY);
	ssize_t buffer_size = SINGLE_BUFFER_SIZE;
	char* buffer = malloc(buffer_size + 1);
	ssize_t ret;
	ret = read(fd, buffer, SINGLE_BUFFER_SIZE);
	while(ret == SINGLE_BUFFER_SIZE)
	{	
		char* temp = realloc(buffer, buffer_size + SINGLE_BUFFER_SIZE + 1);
		if(temp == 0)
		{
			exit(-1);
		}
		buffer = temp;
		ret = read(fd, &buffer[buffer_size], SINGLE_BUFFER_SIZE);
		buffer_size += SINGLE_BUFFER_SIZE;
	}
	return buffer;
}

void checkLogin()
{
	char* username;
	
	printf("Username: ");
	scanf("%16ms", &username);
	if(!strncmp("admin", username, 5))
	{
		printf("Admin login is disabled!\n");
		exit(-1);
	}
	char* userlist = read_userlist();
	char* line = strtok(userlist, "\n");
	char* c_user;
	char* c_password;
	while(line != 0)
	{
		int ret = sscanf(line, "%m[^:]:%m[A-Za-z0-9+/=]", &c_user, &c_password);

		if(ret != 2)
		{
			exit(-1);
		}
		if(strcmp(c_user, username))
		{
			free(c_user);
			free(c_password);
			c_user = 0;
			c_password = 0;
			line = strtok(0, "\n");
		}
		else break;
	}

	if(c_user == 0)
	{
		printf("User not found\n");
		exit(-1);
	}
	if(strlen(c_password) != HASH_SIZE) //todo
	{
		exit(-1);
	}
	checkPassword(c_password);
	
}

int limit_permissions()
{
	int ret = 0;
	struct rlimit r;
	r.rlim_cur = 0;
	r.rlim_max = 0;
	ret += setrlimit(RLIMIT_CORE, &r);
	r.rlim_cur = 5;
	r.rlim_max = 5;
	ret += setrlimit(RLIMIT_CPU, &r);
	r.rlim_cur = 1024;
	r.rlim_max = 1024;
	ret += setrlimit(RLIMIT_FSIZE, &r);
	r.rlim_cur = 32;
	r.rlim_max = 32;
	ret += setrlimit(RLIMIT_NOFILE, &r);
	r.rlim_cur = 16;
	r.rlim_max = 16;
	ret += setrlimit(RLIMIT_NOFILE, &r);
}

int main(int argc, char** argv)
{

	checkLogin();
	puts(argv[1]);
	int ret = chroot(argv[1]);
	ret += chdir("/");
	ret += limit_permissions();
	ret += setgid(1042);
	ret += setuid(1042);
	char* temp[] = {"payload", 0};
	printf("Executing payload...\n\n\n");
	ret = execv("payload", temp);

	printf("Payload could not be executed\n");
	printf("Is it self-contained?\n");
	
	
}
