#include <stdio.h>
#include <curl/curl.h>
#include "comm.h"

void send_post(char* url, char* post_data) {
    CURL *curl;
    CURLcode res;
    FILE *f;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    struct curl_httppost* post = NULL;
    struct curl_httppost* last = NULL;
 
    curl = curl_easy_init();
    if(curl) {
        curl_formadd(&post, &last, 
            CURLFORM_COPYNAME, "file",
            CURLFORM_FILE, "data.wav",
            CURLFORM_END);
        
        curl_formadd(&post, &last,
               CURLFORM_COPYNAME, "data",
               CURLFORM_COPYCONTENTS, post_data,
               CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        
        res = curl_easy_perform(curl);
        if(res)
            printf("curl_easy_perform failed: %d\n", res);
        curl_formfree(post);
        curl_easy_cleanup(curl);
    }
    else
        printf("curl_easy_init failed\n");
    curl_global_cleanup();
    return;
}