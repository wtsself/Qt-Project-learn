#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include<QPushButton>
#include <QString>
#include<QPalette>
#include<QPixmap>
#include<QSize>
#include<QMediaPlayer>//用于多媒体的函数调用
#include<QFile>
#include<QFileInfo>
#include<QDir>
#include<QMessageBox>
#include<QListWidget>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QSqlError>
#include<QTimer>
#include<QStyledItemDelegate>
//导入时间头文件，用于随机事件
#include<time.h>

//动画头文件
#include<QPropertyAnimation>
//用 delegate 来控制 item 的绘制方式
class CenterAlignDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override {
        QStyledItemDelegate::initStyleOption(option, index);
        option->displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//三种音乐播放模式，顺序，随机，循环
enum PLAYMODE{
    ORDER_MODE,//默认值为0，下面依次为1，2
    RANDOM_MODE,
    CIRCLE_MODE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//私有函数，只在本文件调用
private:
    //设置按钮的样式
    void setButtonStyle(QPushButton *button,const QString &filename);
    //初始化按钮
    void initButton();
    //初始化事件
    void init();
    //设置背景
    void setBackGround(const QString &path);
    //加载指定的音乐文件夹
    void loadAppointMusicDir(const QString &filepath);
    //加载指定的音乐
    void  startPlayMusic(int a);
    //设置音乐列表的右侧渐入和渐出的动画
    //显示动画
    void showAnimation(QWidget *window);
    //隐藏动画
    void hideAnimation(QWidget *window);
     // 将毫秒转换为分钟:秒钟格式
    QString handleTimeTranfer(int time);
    //管理播放模式
    void managePlayMode();
    // 专用上限检测槽函数
    void handleSliderMaxReached(int value);
    //初始化数据库连接
    void initdatabase();
    // 更新静音按钮状态
    void updateMuteButton(int volume);
    // 显示音量提示
    void showVolumePopup(int value);
    //滑动播放功能
     void sliderMovedPlay(int position);
    //读取并解析歌词
     void loadLyric(const QString &musicName);
    //绑定播放器播放进度，实时同步歌词
     void updateLyric(qint64 position);
private slots:
    //处理播放和暂停
    //处理换歌暂停转播放,，status是转入转歌前的状态
    void handlePlaySlot(int status);
    //处理播放模式
    void handleModeSlot();
    //下一首
    void handleNextSlot();
    //上一首
    void handlePreSlot();
    //加载播放音乐
    //void handleMusicPlay();
    //处理音乐列表
    void handleListSlot();
    //处理进度条(位置)
    void handlePositionSlot(int position);
    //处理音乐时长
    void handleDurationSlot(int duration);
    //列表点击事件
    void handleListClickedSlot(QListWidgetItem *item);
    //歌曲改变事件
    void handleMediaChangedSlot(const QMediaContent &media);
    //音量显示
    void onVolumeChangedSlot(int value);
    //静音
    void toggleMuteSlot();



// 自定义信号
signals:
    void sliderMaxReached();
private:
    Ui::MainWindow *ui;
    //音乐播放器
    QMediaPlayer *mediaPlayer;
    //当前播放模式
    PLAYMODE playMode;
    //音乐文件路径（绝对路径）
    QString musicPath;
    //将播放音乐的方式传入全局，0表示播放暂停按钮，1表示上一首下一首按钮
    int mode=0;
    //设置音乐列表状态
    bool  musicListStatus;
    //创建数据库对象
    QSqlDatabase db;
    //音量相关变量
    bool isMuted = false;
    int previousVolume = 50;
    QLabel *volumePopup=nullptr;
    // 定义一个成员变量来保存暂停时的进度
    qint64 pausedPosition = 0;
    //歌词--滚动，高亮
    QMap<qint64, QString> lyricMap;
    QList<qint64> lyricTimeList;
    QString currentLyric;
    int currentIndex = -1;
    //判断有无歌词
    bool hasLyric = false;

};
#endif // MAINWINDOW_H
