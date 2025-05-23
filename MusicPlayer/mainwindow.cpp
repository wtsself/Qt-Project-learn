#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),playMode(ORDER_MODE) //初始化播放模式--顺序
    ,musicListStatus(false)//初始化音乐列表状态--默认隐藏
{
    ui->setupUi(this);
    //音乐播放器
    mediaPlayer=new QMediaPlayer;
    mediaPlayer->setParent(this);//等同于mediaPlayer=new QMediaPlayer（this）;
    this->setWindowTitle("音乐播放器");
    //初始化按钮,自定义封装函数
    initButton();
    //初始化事件
    init();
    //初始化当前行
    ui->musicList->setCurrentRow(0);
    //设置随机数种子
    srand(time(NULL));
    //设置背景
    setBackGround(":/image/background-0.png");

    //加载音乐文件夹
    musicPath="D:\\qt-pro\\MusicPlayer\\music\\";
    loadAppointMusicDir(musicPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置按钮的样式
void MainWindow::setButtonStyle(QPushButton *button,const QString &filename){
    //设置按钮的大小
    button->setFixedSize(50,50);
    //设置按钮的图标
    button->setIcon(QIcon(filename));
    //设置图标的大小
    button->setIconSize(QSize(50,50));
    //设置按钮的背景色为透明色,不设置则留有框
    button->setStyleSheet("background-color:transparent");

};
//初始化按钮
void MainWindow::initButton(){
    setButtonStyle(ui->preBtn,":/Icon/pre.png");
    setButtonStyle(ui->playBtn,":/Icon/play.png");
    setButtonStyle(ui->nextBtn,":/Icon/next.png");
    setButtonStyle(ui->modeBtn,":/Icon/order.png");
    setButtonStyle(ui->listBtn,":/Icon/music.png");
    ui->muteBtn->setIcon(QIcon(":/Icon/volume.png"));
    ui->muteBtn->setIconSize(QSize(31,31));
    ui->muteBtn->setStyleSheet("background-color:transparent");
    //信号与槽--按钮
    connect(ui->playBtn,&QPushButton::clicked,this,&MainWindow::handlePlaySlot);
    connect(ui->modeBtn,&QPushButton::clicked,this,&MainWindow::handleModeSlot);
    connect(ui->nextBtn,&QPushButton::clicked,this,&MainWindow::handleNextSlot);
    connect(ui->preBtn,&QPushButton::clicked,this,&MainWindow::handlePreSlot);
    connect(ui->listBtn,&QPushButton::clicked,this,&MainWindow::handleListSlot);

};

//初始化事件
void MainWindow::init(){
    //设置音乐列表样式
    ui->musicList->setStyleSheet("QListWidget{"
                                 "border:none;"
                                 "border-radius:30px;"
                                 "background-image: url(:/image/musicLIist-image.png);}");
    //默认隐藏音乐列表
    ui->musicList->hide();
    //处理音乐位置的变化
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,&MainWindow::handlePositionSlot);
    //处理音乐的总时长
    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,&MainWindow::handleDurationSlot);
    //处理音乐自动播放--自定义一个信号，和槽函数，将实时监测滑动值的改变，当到达设定得最大值时，发送自定义的信号，然后监测接受到了该信号，就执行自动播放函数
    connect(ui->progressSlider,&QSlider::valueChanged,this,&MainWindow::handleSliderMaxReached);
    connect(this,&MainWindow::sliderMaxReached,this,&MainWindow::managePlayMode);
    //设置列表的点击事件--改变音乐
    connect(ui->musicList,&QListWidget::itemClicked,this,&MainWindow::handleListClickedSlot);
    // 初始化音量控件
    ui->volumeSlider->setValue(50);
    mediaPlayer->setVolume(50);

    // 连接信号槽
    connect(ui->volumeSlider, &QSlider::valueChanged,
            this, &MainWindow::onVolumeChangedSlot);
    connect(ui->muteBtn, &QToolButton::clicked,
            this, &MainWindow::toggleMuteSlot);
    //滑动播放
    connect(ui->progressSlider, &QSlider::sliderMoved,
            this, &MainWindow::sliderMovedPlay);

    //歌曲改变事件--改变背景
    connect(mediaPlayer, &QMediaPlayer::currentMediaChanged,this, &MainWindow::handleMediaChangedSlot);
    //初始化数据库连接
    initdatabase();
    //读取并解析歌词
     void loadLyric(const QString &musicName);
     //绑定播放器播放进度，实时同步歌词
     connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::updateLyric);

    //设置高亮行
     ui->lyricListWidget->setAlternatingRowColors(false);


      // 禁止交替绘制--Qt 默认 QListWidget 的 item 是交替着绘制背景的
     ui->lyricListWidget->setItemDelegate(new CenterAlignDelegate(ui->lyricListWidget));
     // 隐藏滚动条
     ui->lyricListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     // 设置样式表：背景全透明 + 居中 + 自定义字体
     ui->lyricListWidget->setStyleSheet(
         "QListWidget {"
         " background: transparent;"
         " border: none;"
         " font-family: 'KaiTi';"
         " font-size: 28px;"
         " color: white;"
         "}"
         "QListWidget::item {"
         " background: transparent;"
         " text-align: center;"           // 有些 Qt 不生效，用 delegate 更稳,该版本5.14不生效
         "}"
         "QListWidget::item:selected {"
         " background: transparent;"
         " color: #00FFFF;"               // 高亮时的颜色（可选）
         "}"
     );

     // 设置列表透明属性
     ui->lyricListWidget->setAttribute(Qt::WA_TranslucentBackground);
     ui->lyricListWidget->viewport()->setAutoFillBackground(false);
     ui->lyricListWidget->setAutoFillBackground(false);


}

 //读取并解析歌词
void MainWindow::loadLyric(const QString &musicName) {
    lyricMap.clear();
    lyricTimeList.clear();
    ui->lyricListWidget->clear();


    QString lrcPath = "D:\\qt-pro\\MusicPlayer\\lyrics\\" + musicName + ".lrc";
    QFile file(lrcPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->lyricListWidget->addItem("当前歌曲暂无歌词");
        return;
    }

    while (!file.atEnd()) {
        QString line = QString::fromUtf8(file.readLine()).trimmed();

        QRegularExpression re("\\[(\\d+):(\\d+\\.\\d+)\\](.*)");
        QRegularExpressionMatch match = re.match(line);
        if (match.hasMatch()) {
            int minute = match.captured(1).toInt();
            double second = match.captured(2).toDouble();
            qint64 timeMs = static_cast<qint64>((minute * 60 + second) * 1000);
            QString text = match.captured(3);
            lyricMap[timeMs] = text;
            lyricTimeList.append(timeMs);
            ui->lyricListWidget->addItem(text);
        }
    }

    file.close();
}

//绑定播放器播放进度，实时同步歌词
void MainWindow::updateLyric(qint64 position) {
    if (lyricMap.isEmpty()) return;

    int index = -1;

    for (int i = 0; i < lyricTimeList.size(); ++i) {
        if (position < lyricTimeList[i]) break;
        index = i;
    }

    if (index != -1 && index != currentIndex) {
        currentIndex = index;

        // 设置当前行高亮
        ui->lyricListWidget->setCurrentRow(index);
        QListWidgetItem *item = ui->lyricListWidget->item(index);
        item->setTextColor(Qt::blue); // 高亮颜色

        // 重置其他行颜色
        for (int i = 0; i < ui->lyricListWidget->count(); ++i) {
            if (i != index) {
                ui->lyricListWidget->item(i)->setTextColor(Qt::white);
            }
        }

        // 自动滚动到当前行
        //ui->lyricListWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
    }
}
//歌曲改变事件--改变背景
void MainWindow::handleMediaChangedSlot(const QMediaContent &content) {
    QUrl mediaUrl = content.request().url();
    QString fileName = mediaUrl.fileName(); // 例如："人间疾苦.mp3"


    // 去掉扩展名 .mp3，得到歌曲名
    QString musicName = fileName.section('.', 0, 0); // 或者 fileName.chopped(4);


    // 更新歌词
   loadLyric(musicName);
    // 查询数据库，找对应的背景图路径
    QSqlQuery query;
    query.prepare("SELECT music_background, music_path FROM music_background WHERE music_name = :name");
    query.bindValue(":name", musicName);

    if (query.exec()) {
        if (query.next()) {
            QString bgName = query.value(0).toString();
            QString pathPrefix = query.value(1).toString();
            QString fullPath = pathPrefix + bgName;
            //qDebug() << "背景图完整路径：" << fullPath;
            // 设置背景图
            setBackGround(fullPath);

        } else {
            qDebug() << "没有找到该音乐名对应的背景图。";
        }
    } else {
        qDebug() << "数据库查询出错：" << query.lastError().text();
    }
}


//初始化数据库连接
void MainWindow::initdatabase(){
    //连接数据库
    db=QSqlDatabase::addDatabase("QMYSQL"); //加载数据库驱动

    //初始化数据库
    db.setDatabaseName("music_player");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open()){
        qDebug()<<"数据库连接提示:连接成功";

    }
    else{
        qDebug()<<"数据库连接提示:连接失败";
    }
}

//滑动播放功能
void MainWindow::sliderMovedPlay(int position){
    // 设置媒体播放器的位置（毫秒）
      mediaPlayer->setPosition(position);
    // 更新进度条
    ui->progressSlider->setValue(position);
    //设置时间展示（分秒）
    QString timeText=handleTimeTranfer(position);
    ui->currentTime->setText(timeText);

};

//更新音量
void MainWindow::onVolumeChangedSlot(int value){
    // 更新播放器音量
    mediaPlayer->setVolume(value);

    // 更新音量按钮图标
    updateMuteButton(value);

    // 显示音量提示
    showVolumePopup(value);

}

//静音按钮
void MainWindow::toggleMuteSlot(){
    if(isMuted) {
        // 取消静音
        mediaPlayer->setVolume(previousVolume);
        ui->volumeSlider->setValue(previousVolume);
    } else {
        // 记录当前音量并静音
        previousVolume = mediaPlayer->volume();
        mediaPlayer->setVolume(0);
        ui->volumeSlider->setValue(0);
    }
    isMuted = !isMuted;
    updateMuteButton(mediaPlayer->volume());

}

// 更新静音按钮状态
void MainWindow::updateMuteButton(int volume)
{
    QString iconPath;
    if(volume == 0) {
        iconPath = ":/Icon/mute.png";
    } else {
        iconPath = ":/Icon/volume.png";
    }

    QIcon icon(iconPath);
    ui->muteBtn->setIcon(icon);
    ui->muteBtn->setIconSize(QSize(31, 31));
}

// 显示音量提示
void MainWindow::showVolumePopup(int value)
{
    // 确保对象已创建
    if(!volumePopup) {
        volumePopup = new QLabel(this);
        volumePopup->setWindowFlags(Qt::ToolTip);
        volumePopup->setStyleSheet("QLabel { background: rgba(0,0,0,200); color: white; padding: 5px; border-radius: 3px; }");
    }

    volumePopup->setText(QString::number(value) + "%");
    volumePopup->move(QCursor::pos() + QPoint(15, 15));
    volumePopup->show();

    // 自动隐藏
    QTimer::singleShot(1000, [this](){
        if(volumePopup) volumePopup->hide();
    });
}

//列表点击事件
void MainWindow::handleListClickedSlot(QListWidgetItem *item){
    QString musicAbsPath= musicPath+item->text()+".mp3";
    //加载音乐
    mediaPlayer->setMedia(QUrl::fromLocalFile(musicAbsPath));
    mediaPlayer->play();

}

//设置背景
void MainWindow::setBackGround(const QString &path){
    //创建照片
    QPixmap pixmap(path);
    //获取窗口大小
    QSize windowSize=this->size();
    //将图片放大或缩小到窗口大小
    QPixmap scalePixmap=pixmap.scaled(windowSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //创建QPalette对象并设置其背景照片-调色板
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(scalePixmap));
    //将调色板应用到窗口
    this->setPalette(palette);
};

//处理播放和暂停
//处理换歌暂停转播放,mode表示是播放按钮播放（0）还是转歌播放（1）
void MainWindow::handlePlaySlot(int status){
    if(mode!=1){
        if (mediaPlayer->state() == QMediaPlayer::PlayingState) {
            // 保存暂停时的进度
            pausedPosition = mediaPlayer->position();
            mediaPlayer->pause();
            ui->playBtn->setIcon(QIcon(":/Icon/play.png"));
        } else {
            QString musicName = ui->musicList->currentItem()->text();
            QString musicAbsPath = musicPath + musicName + ".mp3";
            mediaPlayer->setMedia(QUrl::fromLocalFile(musicAbsPath));

            // 设置播放位置为暂停时的进度
            mediaPlayer->setPosition(pausedPosition);
            mediaPlayer->play();
            ui->playBtn->setIcon(QIcon(":/Icon/stop.png"));
        }
    }
    else{
        if(status==1){

            mediaPlayer->play();
            mode=0;
        }
        else{


            mediaPlayer->pause();
            mode=0;
        }


    }

};


//加载指定的音乐文件夹
void MainWindow::loadAppointMusicDir(const QString &filepath){
    QDir dir(filepath);
    //文件不存在时报错
    if(!dir.exists()){
        QMessageBox::warning(this,"文件夹信息","音乐文件夹打开失败");
        return;
    }
    //使用QDir筛选出文件夹中的文件，并用文件列表接收其返回值
    QFileInfoList filelist=dir.entryInfoList(QDir::Files);
    //遍历文件取出mp3文件
    for(auto element :filelist){
        if(element.suffix()=="mp3"){
            //将文件信息添加到列表中
            ui->musicList->addItem(element.baseName());
        }
    }
    //初始化当前行
    ui->musicList->setCurrentRow(0);

};

//处理播放模式--图标
void MainWindow::handleModeSlot(){
    //点击模式按钮会有规律的切换播放模式并且更换图标
    if(playMode==ORDER_MODE){
        playMode=RANDOM_MODE;
        ui->modeBtn->setIcon(QIcon(":/Icon/random.png"));
    }
    else if(playMode==RANDOM_MODE){
        playMode=CIRCLE_MODE;
        ui->modeBtn->setIcon(QIcon(":/Icon/circle.png"));
    }
    else{
        playMode=ORDER_MODE;
        ui->modeBtn->setIcon(QIcon(":/Icon/order.png"));
    }
}

//处理下一首
void MainWindow::handleNextSlot(){
    //用musicList列表的函数取当前播放行
    int currentRow=ui->musicList->currentRow();
    //初始化下一行号
    int nextRow=0;
    //根据不同的播放模式选择选择下一行为谁
    if(playMode==ORDER_MODE){
        nextRow=(currentRow+1)%(ui->musicList->count());
    }
    else if(playMode==CIRCLE_MODE){//单曲循环
        nextRow=currentRow;
    }
    else{//随机
        int count=0;//避免死循环，设置最大随机同一事件的次数，超过这个次数,则默认为下一首
        do{
            nextRow=rand()%ui->musicList->count();
        }while(nextRow==currentRow&&(count<=3));
        if(count>3){
            nextRow=(currentRow+1)%(ui->musicList->count());
        }

    }
    //设置下一行为当前行
    ui->musicList->setCurrentRow(nextRow);
    //判断当前的状态，在转入下一首歌时传入状态
    if( mediaPlayer->state()==QMediaPlayer::PlayingState){
        startPlayMusic(1);
    }
    else{
        startPlayMusic(0);
    }



}


//处理上一首
void MainWindow::handlePreSlot(){

    int currentRow=ui->musicList->currentRow();

    int preRow=0;

    if(playMode==ORDER_MODE){
        if(currentRow-1>=0){
            preRow=currentRow-1;
        }
        else {
            preRow=ui->musicList->count()-1;//注意是0开始计数
        }
    }
    else if(playMode==CIRCLE_MODE){//单曲循环
        preRow=currentRow;
    }
    else{//随机
        int count=0;//避免死循环，设置最大随机同一事件的次数，超过这个次数，则默认为下一首
        do{
            preRow=rand()%ui->musicList->count();
        }while(preRow==currentRow&&(count<=3));
        if(count>3){
            preRow=(currentRow+1)%(ui->musicList->count());
        }
    }
    //设置上一行为当前行
    ui->musicList->setCurrentRow(preRow);
    //判断当前的状态，在转入上一首歌时传入状态
    if( mediaPlayer->state()==QMediaPlayer::PlayingState){
        startPlayMusic(1);
    }
    else{
        startPlayMusic(0);
    }

}

//加载指定的音乐
void  MainWindow::startPlayMusic(int a){
    //获取音乐列表的音乐名，然后与音乐文件路径拼接得到音乐的绝对路径
    QString musicName= ui->musicList->currentItem()->text();

    QString musicAbsPath= musicPath+musicName+".mp3";
    //加载音乐
    mediaPlayer->setMedia(QUrl::fromLocalFile(musicAbsPath));
    //背景随音乐变化



    mode=1;
    if(a==1){//播放状态

        handlePlaySlot(1);
    }
    else{

        handlePlaySlot(0);
    }


};

//处理音乐列表
void MainWindow::handleListSlot(){
    if(musicListStatus==false){

        ui->musicList->show();
        //以渐入的动画方式出现列表，先显现列表，将其放在窗口位置以外地方逐渐移入窗口界面
        showAnimation(ui->musicList);

        musicListStatus=true;

    }
    else {

        //以渐出的动画方式隐藏列表，先将列表移出窗口再隐藏
        hideAnimation(ui->musicList);

        ui->musicList->hide();
        musicListStatus=false;
    }


};

//显示动画
void MainWindow::showAnimation(QWidget *window){
    //创建动画对象
    QPropertyAnimation animation(window,"pos");
    //动画持续时间
    animation.setDuration(100);
    //起始坐标
    animation.setStartValue(QPoint(this->width(),0));
    //结束坐标
    animation.setEndValue(QPoint((this->width())-(ui->musicList->width()),0));
    //动画开始
    animation.start();
    //信号与槽，处理动画循环，等待动画结束
    QEventLoop loop;
    connect(&animation,&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
    loop.exec();
};
//隐藏动画
void MainWindow::hideAnimation(QWidget *window){

    //创建动画对象
    QPropertyAnimation animation(window,"pos");
    //动画持续时间
    animation.setDuration(100);
    //起始坐标
    animation.setStartValue(QPoint((this->width())-(ui->musicList->width()),0));

    //结束坐标

    animation.setEndValue(QPoint(this->width(),0));


    //动画开始
    animation.start();
    //信号与槽，处理动画循环，等待动画结束
    QEventLoop loop;
    connect(&animation,&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
    loop.exec();


};

//管理播放模式--自动播放音乐设置
void MainWindow::managePlayMode(){

    //用musicList列表的函数取当前播放行
    int currentRow=ui->musicList->currentRow();
    //初始化下一行号
    int nextRow=0;
    if(playMode==ORDER_MODE){
        nextRow=(currentRow+1)%(ui->musicList->count());
    }
    else if(playMode==CIRCLE_MODE){//单曲循环
        nextRow=currentRow;
    }
    else{//随机
        int count=0;//避免死循环，设置最大随机同一事件的次数，超过这个次数,则默认为下一首
        do{
            nextRow=rand()%ui->musicList->count();
        }while(nextRow==currentRow&&(count<=3));
        if(count>3){
            nextRow=(currentRow+1)%(ui->musicList->count());
        }

    }
    //设置下一行为当前行
    ui->musicList->setCurrentRow(nextRow);

    //获取音乐列表的音乐名，然后与音乐文件路径拼接得到音乐的绝对路径
    QString musicName= ui->musicList->currentItem()->text();

    QString musicAbsPath= musicPath+musicName+".mp3";
    //加载音乐
    mediaPlayer->setMedia(QUrl::fromLocalFile(musicAbsPath));
    mediaPlayer->play();

};

// 处理进度条
void MainWindow::handlePositionSlot(int position){
    // 更新进度条
    ui->progressSlider->setValue(position);
    QString timeText=handleTimeTranfer(position);



    ui->currentTime->setText(timeText);


};

// 处理音乐时长
void MainWindow::handleDurationSlot(int duration){
    // 设置音乐总时长
    ui->progressSlider->setRange(0, duration);

    QString durationText=handleTimeTranfer(duration);


    ui->totalTime->setText(durationText);

};

// 将毫秒转换为分钟:分秒格式
QString MainWindow::handleTimeTranfer(int time){
    // 将毫秒转换为分钟:秒钟格式
    int totalSeconds = time / 1000;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    // 格式化为两位数显示（00:00）
    QString durationText = QString("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
    return durationText;

}

// 在检测到最大值时发送信号
void MainWindow::handleSliderMaxReached(int value)
{
    if(value == ui->progressSlider->maximum()) {
        emit sliderMaxReached();  // 发送信号
    }
}


