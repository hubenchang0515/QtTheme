#ifndef ZIP_PACKER_H
#define ZIP_PACKER_H

#include <zip.h>
#include <QObject>

namespace QtTheme
{

class ZipPacker : public QObject
{
public:
    ZipPacker(QObject* parent=nullptr) noexcept;
    ~ZipPacker() noexcept;

    bool open() noexcept;
    void close() noexcept;
    bool addDir(const QString& path) noexcept;
    bool addFile(const QString& filename, const QByteArray& data) noexcept;
    QByteArray data() noexcept;

private:
    zip_source_t* m_source;
    zip_t* m_zip;
};

} // namespace QtTheme


#endif // ZIP_PACKER_H