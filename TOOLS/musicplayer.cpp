#include "musicplayer.h"

MusicPlayer* MusicPlayer::instance = nullptr;
QMutex MusicPlayer::mutex;

MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent)
{
    //构造函数
    player = new QMediaPlayer(this); // 创建音频播放器
    audioOutput=new QAudioOutput(this); //创建播放类。
 //   playerList=new QMediaPlaylist(this);
    player->setAudioOutput(audioOutput);
}

MusicPlayer* MusicPlayer::getInstance(QObject* parent)
{
    if (instance == nullptr)
    {
        QMutexLocker locker(&mutex);
        if (instance == nullptr)
        {
            instance = new MusicPlayer(parent);
        }
    }
    return instance;
}

void MusicPlayer::init(const QVector<QPair<QString, QString> >& musicList)
{
    // 初始化函数
    musicMap.clear();                                 // 清空音乐列表
    for (const auto& pair : musicList) {               // 将传入参数中的音频资源插入QMap
        musicMap.insert(pair.first, pair.second);
    }
    m_volume=50;
}

void MusicPlayer::setNowMusic(QString musicName)
{
    QString musicPath = musicMap.value(musicName);

//    playerList->clear();
//    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
//    playerList->addMedia(QUrl(musicPath));
//    player->setPlaylist(playerList);
//    player->setVolume(m_volume);                      // 设置音量，0-100
//    player->play();                                   // 开始播放操作


    player->setSource(QUrl(musicPath));
    player->setLoops(QMediaPlayer::Once);
    audioOutput->setVolume(m_volume);
    player->play();

}
MusicPlayer::~MusicPlayer()
{
    delete player;
}

void MusicPlayer::play()
{
    if (player->playbackState() == QMediaPlayer::StoppedState) {
        player->setPosition(0); //从头开始
    }
    player->play();
}

void MusicPlayer::pause()
{
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
    }
}

void MusicPlayer::stop()
{
    if (player->playbackState() != QMediaPlayer::StoppedState) {
        player->stop();
    }
}

void MusicPlayer::setVolume(int volume)
{
    m_volume=volume;
    audioOutput->setVolume(m_volume);
}

void MusicPlayer::musicChanged(QString musicName)
{
    emit musicChangedSignal(musicName);
}

void MusicPlayer::playMusic(QString musicName)
{
    QString musicPath = musicMap.value(musicName);

    player->setSource(QUrl(musicPath));
    player->setLoops(QMediaPlayer::Once);
    audioOutput->setVolume(m_volume);
    player->play();

}

void MusicPlayer::setLoop(bool isLoop)
{
    if (isLoop) {
        //playerList->setPlaybackMode(QMediaPlaylist::Loop);
        player->setLoops(QMediaPlayer::Infinite);
    } else {
        //playerList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        player->setLoops(QMediaPlayer::Once);
    }
}

void MusicPlayer::cancelLoop()
{
     player->setLoops(QMediaPlayer::Once);
}

//#include "musicplayer.h"

//MusicPlayer* MusicPlayer::instance = nullptr;
//QMutex MusicPlayer::mutex;

//MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent)
//{
//    player = new QMediaPlayer(this); // 创建音频播放器
//}

//MusicPlayer* MusicPlayer::getInstance(QObject* parent)
//{
//    if (instance == nullptr)
//    {
//        QMutexLocker locker(&mutex);
//        if (instance == nullptr)
//        {
//            instance = new MusicPlayer(parent);
//        }
//    }
//    return instance;
//}

//void MusicPlayer::init(const QVector<QPair<QString, QString>>& musicList)
//{
//    this->musicList.clear();                          // 清空音乐列表
//    for (const auto& pair : musicList) {               // 将传入参数中的音频资源插入QStringList
//        this->musicList.append(pair.second);
//    }
//    currentMusicIndex = -1;
//    m_volume=50;
//}

//void MusicPlayer::setNowMusic(const QString& musicName)
//{
//    int index = musicList.indexOf(musicName);         // 获取当前音乐在QStringList中的下标
//    if (index >= 0) {
//        currentMusicIndex = index;                    // 设置为当前背景音乐的下标
//        player->setMedia(QUrl(musicName));             // 直接使用QMediaPlayer对象播放该音乐路径
//        player->setVolume(m_volume);                   // 设置音量，0-100
//        player->play();                                // 开始播放操作
//    }
//}

//void MusicPlayer::setLoop(bool isLoop)
//{
//    if (isLoop) {
//        player->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//    } else {
//        player->setPlaybackMode(QMediaPlaylist::Sequential);
//    }
//}

//void MusicPlayer::cancelLoop()
//{
//    player->setPlaybackMode(QMediaPlaylist::Sequential);
//}

//int MusicPlayer::getCurrentMusicIndex() const
//{
//    return currentMusicIndex;
//}

//void MusicPlayer::setCurrentMusicIndex(int index)
//{
//    if (index >= 0 && index < musicList.size()) {
//        currentMusicIndex = index;
//    }
//}

//void MusicPlayer::playMusic()
//{
//    setCurrentMusicIndex(0); // 将当前播放音乐下标设置为0
//    player->setMedia(QUrl(musicList[currentMusicIndex])); // 设置要播放的媒体源

//    player->setVolume(m_volume); // 设置音量
//    player->setPlaybackRate(1); // 恢复正常播放速度
//    player->play();
//}

//void MusicPlayer::play()
//{
//    if (player->state() == QMediaPlayer::StoppedState) {
//        setCurrentMusicIndex(0);
//        player->setMedia(QUrl(musicList[currentMusicIndex]));
//    }
//    player->play();
//}

//void MusicPlayer::pause()
//{
//    if (player->state() == QMediaPlayer::PlayingState) {
//        player->pause();
//    }
//}

//void MusicPlayer::stop()
//{
//    if (player->state() != QMediaPlayer::StoppedState) {
//        player->stop();
//    }
//}

//void MusicPlayer::setVolume(int volume)
//{
//    m_volume=volume;
//    player->setVolume(m_volume);
//}

//void MusicPlayer::playNext()
//{
//    int nextIndex = currentMusicIndex + 1;
//    if (nextIndex < musicList.size()) {
//        currentMusicIndex = nextIndex;
//        player->setMedia(QUrl(musicList.at(currentMusicIndex)));
//        player->play();
//    }
//}

//void MusicPlayer::playPrev()
//{
//    int prevIndex = currentMusicIndex - 1;
//    if (prevIndex >= 0) {
//        currentMusicIndex = prevIndex;
//        player->setMedia(QUrl(musicList.at(currentMusicIndex)));
//        player->play();
//    }
//}

//MusicPlayer::~MusicPlayer()
//{
//    delete player;
//    instance = nullptr;
//}
