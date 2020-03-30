#ifndef MUSICPLAYERWINDOW_H
#define MUSICPLAYERWINDOW_H

#include <QWidget>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

namespace Ui {
class MusicPlayerWindow;
}

class MusicPlayerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayerWindow(QWidget *parent = nullptr);
    ~MusicPlayerWindow();

    void openFile();
    void addToPlayList(const QList<QUrl> &urls);

private slots:
    void playMusic();
    void stopMusic();
    void nextMusic();
    void previousMusic();
    void changeVolume();
    void muteMusic();
    void seekMusic(int seconds);
    void playbackModeChanged();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void statusChanged(QMediaPlayer::MediaStatus status);
    void bufferingProgress(int progress);

private:
    Ui::MusicPlayerWindow *ui;

    QMediaPlayer* mediaPlayer = nullptr;
    QMediaPlaylist* mediaPlayerList = nullptr;
    QTime durationTime;
};

#endif // MUSICPLAYERWINDOW_H
