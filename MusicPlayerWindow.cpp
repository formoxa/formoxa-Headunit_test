#include "MusicPlayerWindow.h"
#include "ui_MusicPlayerWindow.h"

MusicPlayerWindow::MusicPlayerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayerWindow)
{
    ui->setupUi(this);

    // 建立撥放器並初始化設定
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioRole(QAudio::MusicRole); // 撥放形式
    mediaPlayer->setVolume(30); // 初始化音量
    ui->slider_Volume->setValue(30); // 音量 Slider 顯示對應位置
    // 建立撥放列表
    mediaPlayerList = new QMediaPlaylist;
    mediaPlayerList->setPlaybackMode(QMediaPlaylist::Sequential); // 設定撥放順序為依序
    mediaPlayer->setPlaylist(mediaPlayerList);

    // 撥放控制
    QObject::connect(ui->pushButton_PlayPause, &QPushButton::clicked, this, &MusicPlayerWindow::playMusic); // 撥放音樂
    QObject::connect(ui->pushButton_Stop, &QPushButton::clicked, this, &MusicPlayerWindow::stopMusic); // 停止音樂
    QObject::connect(ui->pushButton_Next, &QPushButton::clicked, this, &MusicPlayerWindow::nextMusic); // 下一首
    QObject::connect(ui->pushButton_Previous, &QPushButton::clicked, this, &MusicPlayerWindow::previousMusic); // 上一首
    QObject::connect(ui->slider_Volume, &QSlider::valueChanged, this, &MusicPlayerWindow::changeVolume); // 調整音量
    QObject::connect(ui->pushButton_Mute, &QPushButton::clicked, this, &MusicPlayerWindow::muteMusic); // 靜音
    QObject::connect(ui->slider_Progress, &QSlider::sliderMoved, this, &MusicPlayerWindow::seekMusic); // 拉進度條跳時間
    QObject::connect(ui->pushButton_PlaybackMode, &QPushButton::clicked, this, &MusicPlayerWindow::playbackModeChanged); // 設定撥放順序模式

    // 連結其他功能或顯示
    QObject::connect(mediaPlayer, &QMediaPlayer::durationChanged, this,  &MusicPlayerWindow::durationChanged); // 撥放總時間
    QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, this,  &MusicPlayerWindow::positionChanged); // 已撥放時間
    QObject::connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MusicPlayerWindow::statusChanged); // 媒體狀態回饋
    QObject::connect(mediaPlayer, &QMediaPlayer::bufferStatusChanged, this, &MusicPlayerWindow::bufferingProgress); // 媒體讀取進度回饋

    // 其他控制
    QObject::connect(ui->pushButton_OpenFile, &QPushButton::clicked, this, &MusicPlayerWindow::openFile); // 讀取檔案
    QObject::connect(ui->pushButton_Close, &QPushButton::clicked, this, &MusicPlayerWindow::close); // 關閉視窗

    // 按鈕圖片初始化
    ui->pushButton_PlayPause->setIcon(QIcon(":/Buttons/Play.svg"));
    ui->pushButton_Stop->setIcon(QIcon(":/Buttons/Stop.svg"));
    ui->pushButton_Next->setIcon(QIcon(":/Buttons/Next.svg"));
    ui->pushButton_Previous->setIcon(QIcon(":/Buttons/Previous.svg"));
    ui->pushButton_Mute->setIcon(QIcon(":/Buttons/Mute.svg"));
    ui->pushButton_PlaybackMode->setIcon(QIcon(":/Buttons/Sequential.svg"));
    ui->pushButton_OpenFile->setIcon(QIcon(":/Buttons/OpenFile.svg"));
    ui->pushButton_Close->setIcon(QIcon(":/Buttons/Close.svg"));
}

MusicPlayerWindow::~MusicPlayerWindow()
{
    delete ui;
}

// 音樂控制撥放或暫停
void MusicPlayerWindow::playMusic()
{
    if(mediaPlayerList->isEmpty()) return;
    QMediaPlayer::State mediaState = mediaPlayer->state();
    switch(mediaState)
    {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        ui->pushButton_PlayPause->setIcon(QIcon(":/Buttons/Play.svg"));
        break;
    case QMediaPlayer::PausedState:
        mediaPlayer->play();
        ui->pushButton_PlayPause->setIcon(QIcon(":/Buttons/Pause.svg"));
        break;
    case QMediaPlayer::StoppedState:
        mediaPlayer->play();
        ui->pushButton_PlayPause->setIcon(QIcon(":/Buttons/Pause.svg"));
        break;
    }
}

// 音樂控制停止
void MusicPlayerWindow::stopMusic()
{
    mediaPlayer->stop();
    ui->pushButton_PlayPause->setIcon(QIcon(":/Buttons/Play.svg"));
}

// 下一首
void MusicPlayerWindow::nextMusic()
{
    mediaPlayerList->next();
}

// 上一首
void MusicPlayerWindow::previousMusic()
{
    if(mediaPlayer->position() <= 5000) // 撥放時間若小於 5 秒，才會跳至上一首
    {
        mediaPlayerList->previous();
    }else{
        mediaPlayer->setPosition(0); // 撥放時間若大於 5 秒，則跳至 0 秒撥放
    }
}

// 拉動 Slider 調整音量
void MusicPlayerWindow::changeVolume()
{
    mediaPlayer->setVolume(ui->slider_Volume->value());
}

// 靜音
void MusicPlayerWindow::muteMusic()
{
    if(!mediaPlayer->isMuted())
    {
        mediaPlayer->setMuted(true);
    }else{
        mediaPlayer->setMuted(false);
    }
}

// 拉進度條跳時間
void MusicPlayerWindow::seekMusic(int seconds)
{
    mediaPlayer->setPosition(seconds*1000); // 輸入為 Milliseconds
}

// 設定撥放順序模式
void MusicPlayerWindow::playbackModeChanged()
{
    QMediaPlaylist::PlaybackMode playbackMode = mediaPlayerList->playbackMode();
    switch(playbackMode)
    {
    case QMediaPlaylist::Sequential:
        mediaPlayerList->setPlaybackMode(QMediaPlaylist::Loop); // 全部循環
        ui->pushButton_PlaybackMode->setIcon(QIcon(":/Buttons/Loop.svg"));
        break;
    case QMediaPlaylist::Loop:
        mediaPlayerList->setPlaybackMode(QMediaPlaylist::Random); // 隨機
        ui->pushButton_PlaybackMode->setIcon(QIcon(":/Buttons/Random.svg"));
        break;
    case QMediaPlaylist::Random:
        mediaPlayerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); // 目前撥放循環
        ui->pushButton_PlaybackMode->setIcon(QIcon(":/Buttons/CurrentItemInLoop.svg"));
        break;
    case QMediaPlaylist::CurrentItemInLoop:
        mediaPlayerList->setPlaybackMode(QMediaPlaylist::Sequential); // 依序撥放
        ui->pushButton_PlaybackMode->setIcon(QIcon(":/Buttons/Sequential.svg"));
        break;
    }
}

// 調整進度條 Slider 的最大值
void MusicPlayerWindow::durationChanged(qint64 duration)
{
    // 設定進度條最大值
    ui->slider_Progress->setMaximum(duration/1000);
}

// 顯示撥放進度於進度條及撥放時間
void MusicPlayerWindow::positionChanged(qint64 position)
{
    if(!ui->slider_Progress->isSliderDown()) // 進度條若按下則視為拉進度條跳時間
    {
        // 設定進度條位置
        ui->slider_Progress->setValue(position/1000);

        // 撥放時間 qint64 Millisecond 轉換成 int 的 Hour, Min, Sec
        int position_sec = (position/1000) % 60;
        int position_min = (position/1000/60) % 60;
        int position_hour = (position/1000/60/60) % 60;

        QTime positionTime(position_hour, position_min, position_sec);

        ui->label_CurrentTime->setText(positionTime.toString("hh:mm:ss"));

        // 剩餘撥放時間 qint64 Millisecond 轉換成 int 的 Hour, Min, Sec
        qint64 leftDuration = mediaPlayer->duration() - mediaPlayer->position();
        int left_sec = (leftDuration/1000) % 60;
        int left_min = (leftDuration/1000/60) % 60;
        int left_hour = (leftDuration/1000/60/60) % 60;

        QTime leftTime(left_hour, left_min, left_sec);

        ui->label_LeftTime->setText(leftTime.toString("hh:mm:ss"));
    }
}

// // 處理 MediaPlayer 目前狀態，給予使用者訊息
void MusicPlayerWindow::statusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
    case QMediaPlayer::LoadedMedia:
        //setStatusInfo(QString());
        break;
    case QMediaPlayer::LoadingMedia:
        //setStatusInfo(tr("Loading..."));
        break;
    case QMediaPlayer::BufferingMedia:
    case QMediaPlayer::BufferedMedia:
        //setStatusInfo(tr("Buffering %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::StalledMedia:
        //setStatusInfo(tr("Stalled %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::EndOfMedia:
        //QApplication::alert(this);
        break;
    case QMediaPlayer::InvalidMedia:
        //displayErrorMessage();
        break;
    }
}

// 處理 MediaPlayer 目前 Buffering 狀態，給予使用者已讀取進度訊息
void MusicPlayerWindow::bufferingProgress(int progress)
{
    if(mediaPlayer->mediaStatus() == QMediaPlayer::StalledMedia)
    {
        //setStatusInfo(tr("Stalled %1%").arg(progress));
    }else{
        //setStatusInfo(tr("Buffering %1%").arg(progress));
    }
}

// 開啟選擇檔案視窗讀入音樂檔案
void MusicPlayerWindow::openFile()
{
    QFileDialog fileDialog;
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen); // 開啟模式
    fileDialog.setWindowTitle(tr("Open Files"));
    //QStringList supportedMimeTypes = mediaPlayer->supportedMimeTypes(); // supportedMimeTypes() 已經過時的 function 無法再用
    QStringList supportedMimeTypes = {"audio/mpeg", "audio/aac", "audio/vnd.wave", "audio/x-flac", "audio/vnd.rn-realaudio", "audio/x-m3u"}; // 指定要過濾的 MIME
    if(!supportedMimeTypes.empty())
        fileDialog.setMimeTypeFilters(supportedMimeTypes); // 過濾開啟檔案類型
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath())); // 預設資料夾，若沒有 MusicLocation 則讀取 homePath()
    if(fileDialog.exec() == QDialog::Accepted) // 選擇檔案後按下開啟
    {
        addToPlayList(fileDialog.selectedUrls());
    }
}

// 判斷讀取檔案是否為 .m3u 歌單
static bool isPlayList(const QUrl& url)
{
    if(!url.isLocalFile()) return false;
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

// 讀入選取檔案，並判斷若為歌單則將歌單讀入 PlayList，若為檔案則加入現有 PlayList
void MusicPlayerWindow::addToPlayList(const QList<QUrl> &urls)
{
    for(auto& url : urls)
    {
        if(isPlayList(url))
        {
            mediaPlayerList->load(url);
        }else{
            mediaPlayerList->addMedia(url);
        }
    }
}
