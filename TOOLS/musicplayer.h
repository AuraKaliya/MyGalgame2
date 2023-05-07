    #ifndef MUSICPLAYER_H
    #define MUSICPLAYER_H

    #include <QObject>
    #include <QMap>
    #include <QMediaPlayer>
   // #include <QMediaPlaylist>
    #include <QAudioOutput>
    #include <QMutex>

    class MusicPlayer : public QObject
    {
        Q_OBJECT
    public:
        static MusicPlayer* getInstance(QObject* parent = nullptr); //获取单例对象
        void init(const QVector<QPair<QString, QString> >& musicList);  //初始化函数，传入参数为包含音乐名和资源路径的QVector


        void setNowMusic(QString musicName); //设置当前播放的背景音乐，函数名为setNowMusic，传入参数为QString

        void setLoop(bool isLoop=true);
        void cancelLoop();


    public slots:
        void musicChanged(QString musicName);  //更换音乐
        void playMusic(QString musicName); //播放背景音乐
        void play();        // 播放音乐
        void pause();       // 暂停音乐
        void stop();        // 停止音乐
        void setVolume(int volume); // 设置音量



    signals:
        void musicChangedSignal(QString);

    private:
        static MusicPlayer* instance;
        static QMutex mutex;
        QMap<QString, QString> musicMap; //一个QMap存放音乐类资源
        QMediaPlayer* player;            // 音频播放器指针
        QAudioOutput* audioOutput;
      //  QMediaPlaylist * playerList;
        QString nowMusic; // 当前正在播放的背景音乐的名字
        int m_volume;
        explicit MusicPlayer(QObject *parent = nullptr);
        MusicPlayer(const MusicPlayer&);

        ~MusicPlayer();
    };

    #endif // MUSICPLAYER_H


//    #ifndef MUSICPLAYER_H
//    #define MUSICPLAYER_H

//    #include <QObject>
//    #include <QStringList>
//    #include <QMediaPlayer>
//    // #include <QMediaPlaylist>
//    #include <QMutex>

//    class MusicPlayer : public QObject
//    {
//        Q_OBJECT
//    public:
//        static MusicPlayer* getInstance(QObject* parent = nullptr); //获取单例对象
//        void init(const QVector<QPair<QString, QString>>& musicList);  //初始化函数，传入参数为包含音乐名和资源路径的QVector

//        void setNowMusic(const QString& musicName); //设置当前播放的背景音乐，函数名为setNowMusic，传入参数为QString

//        void setLoop(bool isLoop);
//        void cancelLoop();

//        int getCurrentMusicIndex() const;
//        void setCurrentMusicIndex(int index);

//    public slots:
//        void playMusic(); //播放背景音乐
//        void play();        // 播放音乐
//        void pause();       // 暂停音乐
//        void stop();        // 停止音乐
//        void setVolume(int volume); // 设置音量
//        void playNext();    // 播放下一首音乐
//        void playPrev();    // 播放上一首音乐

//    signals:
//        void musicChangedSignal(QString);

//    private:
//        static MusicPlayer* instance;
//        static QMutex mutex;
//        QStringList musicList; //存储音乐路径
//        QMediaPlayer* player;            // 音频播放器指针
//        int currentMusicIndex; // 当前正在播放的背景音乐在QStringList中的下标
//        int m_volume;
//        explicit MusicPlayer(QObject *parent = nullptr);
//        MusicPlayer(const MusicPlayer&);
//        ~MusicPlayer();
//    };

//    #endif // MUSICPLAYER_H
