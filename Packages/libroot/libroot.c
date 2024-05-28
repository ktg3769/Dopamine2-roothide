#include <roothide.h>
#include <uuid/uuid.h>
#include <limits.h>

static char g_jbroot_prefix[PATH_MAX] = {0};
static uuid_string_t g_boot_uuid = {0};

__attribute__((constructor)) static void initializer(void)
{
	uint64_t jbranduuid[2] = {jbrand(), jbrand()};
	uuid_unparse(*(uuid_t*)&jbranduuid, g_boot_uuid);

	strcpy(g_jbroot_prefix, jbroot("/"));
	size_t len = strlen(g_jbroot_prefix);
	if(g_jbroot_prefix[len]=='/') g_jbroot_prefix[len]='\0';
}

const char *libroot_get_root_prefix(void)
{
	return "/rootfs";
}

const char *libroot_get_jbroot_prefix(void)
{
	return g_jbroot_prefix;
}

const char *libroot_get_boot_uuid(void)
{
	return g_boot_uuid;
}

char *libroot_dyn_rootfspath(const char *path, char *resolvedPath)
{
	const char* newpath = rootfs(path);
	if(!newpath) return NULL;
	strcpy(resolvedPath, newpath);
	return resolvedPath;
}

char *libroot_dyn_jbrootpath(const char *path, char *resolvedPath)
{
	const char* newpath = jbroot(path);
	if(!newpath) return NULL;
	strcpy(resolvedPath, newpath);
	return resolvedPath;
}
