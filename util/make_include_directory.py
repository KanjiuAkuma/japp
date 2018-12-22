import os
import re
import shutil

regex = re.compile(".hp{0,2}$")


def deleteDir(path):
    if os.path.exists(path):
        for entry in os.scandir(path):
            if entry.is_dir():
                deleteDir(entry.path)
            else:
                os.remove(entry.path)


def getFilesR(root_dir, sub_dir):
    if "vendor" in sub_dir:
        return []
    m_path = root_dir + "\\" + sub_dir
    print("Scanning '%s'" % sub_dir)
    out = []
    for entry in os.scandir(m_path):
        if entry.is_file():
            if regex.search(entry.name):
                path = sub_dir + "\\" + entry.name
                # print("Found '%s'" % path)
                out.append(path)
        else:
            out += getFilesR(root_dir, sub_dir + "\\" + entry.name)
    return out


if __name__ == '__main__':
    print("Collecting header files")
    root = os.path.realpath(os.path.dirname(__file__) + "\\..\\")
    src_path = root + "JApp\\src"
    include_path = root + "include"

    # delete includes
    deleteDir(include_path)

    files = getFilesR(src_path, "")
    print("Collected %d files" % len(files))
    for f in files:
        src = src_path + f
        dst = include_path + f
        print("Copying '%s' -> '%s'" % (src, dst))
        folder = os.path.dirname(dst)
        os.makedirs(folder, 0o777, True)
        shutil.copyfile(src, dst)
    # input("Press enter to exit...")
