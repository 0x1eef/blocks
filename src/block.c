#include <blocks/alloc.h>
#include <blocks/block.h>
#include <errno.h>
#include <string.h>
#include <curl/curl.h>
#include <sysexits.h>

char *
block_path(block *self)
{
  char *home           = getenv("HOME");
  const char *filename = self->filename;
  if (home)
  {
    char *relpath  = "/.local/share/blocks/", *fullpath;
    size_t offset1 = strlen(home), offset2 = strlen(relpath),
           bufsize = offset1 + offset2 + strlen(filename) + 1;
    fullpath       = alloc(sizeof(char) * bufsize);
    memcpy(&fullpath[0], home, offset1);
    memcpy(&fullpath[offset1], relpath, offset2);
    memcpy(&fullpath[offset1 + offset2], filename, strlen(filename) + 1);
    return (fullpath);
  }
  else
  {
    return NULL;
  }
}

int
block_write(const char *path, const char *url)
{
  FILE *file;
  file = fopen(path, "w");
  if (file == NULL)
  {
    return (-1);
  }
  else
  {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(file);
    return (res);
  }
}
