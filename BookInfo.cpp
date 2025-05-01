//
// Created by momer on 4/29/2025.
//
#include "BookInfo.h"

Text::Text(QWidget *parent, int window_x, int window_y) : QWidget(parent){

    //Network manager
    manager = new QNetworkAccessManager(this);

    //Title Text
    QFont font1;
    font1.setPixelSize(16);
    int title_x = window_x/4;
    int title_y = window_y/6;
    text_items.append(text_items_strc("Title:", font1, QColor(0,0,0), QPoint(title_x, title_y), 200, true));

    QFont font1t;
    font1.setPixelSize(16);
    int title_xt = (window_x/4) + 100;
    int title_yt = window_y/6;
    text_items.append(text_items_strc(book_title, font1, Qt::black, QPoint(title_xt, title_yt), 200, true));

    //Author Text
    QFont font2;
    font1.setPixelSize(16);
    int author_x = window_x/4;
    int author_y = window_y/4.5;
    text_items.append(text_items_strc("Author:", font1, Qt::black, QPoint(author_x, author_y), 200, true));

    QFont font2a;
    font1.setPixelSize(16);
    int author_xa = (window_x/4) + 100;
    int author_ya = window_y/4.5;
    text_items.append(text_items_strc(book_author, font1, Qt::black, QPoint(author_xa, author_ya), 200, true));

}

Text::~Text() {
    delete manager;
}

void Text::get_book_info(const QString &workId, const std::function<void(QString, QString)>& callback){

    //HTML page for book
    QUrl url(QString("http://openlibrary.org/works/%1.json").arg(workId));
    QNetworkRequest request(url);
    //GET request for HTML
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, callback, this](){
        QString get_title = "Unknown";
        QString get_author = "Unknown";
        bool multi_authors = false;

        if(reply->error() == QNetworkReply::NoError){
            //extracts complete response in a pure byte array
            //contains raw Json data returned
            QByteArray data = reply->readAll();
            //converts raw JSON data into a QJsonDocument object
            //converts data into a structual format
            QJsonDocument doc  = QJsonDocument::fromJson(data);
            //returns root objects which allows us access to the data we need
            QJsonObject json_obj = doc.object();

            //title of book
            get_title = json_obj["title"].toString();


            //get author
            if(json_obj.contains("authors") && json_obj["authors"].isArray()){
                //Makes a Json array out of the authors
                QJsonArray author_list = json_obj["authors"].toArray();
                //sets true if author_list is greater than 1
                multi_authors = (author_list.size() > 1);

                if(!author_list.isEmpty()){
                    QJsonObject author_obj = author_list[0].toObject();
                    //this will get the key which allows us to go to the
                    //Author page allowing us to access to his name
                    if(author_obj.contains("author")){
                        //allowing me to access author_key
                        QJsonObject author_ref = author_obj["author"].toObject();
                        //the key to the author
                        QString author_key = author_ref["key"].toString();

                        //HTML Page for author
                        QUrl author_url(QString("http://openlibrary.org%1.json").arg(author_key));
                        QNetworkRequest author_request(author_url);
                        //GET request for HTML
                        QNetworkReply *author_reply = manager->get(author_request);

                        QObject::connect(author_reply, &QNetworkReply::finished, [author_reply, get_title, callback, multi_authors](){
                            QString get_author = "Unknown";

                            if(author_reply->error() == QNetworkReply::NoError){
                                QByteArray author_data = author_reply->readAll();
                                QJsonDocument author_doc = QJsonDocument::fromJson(author_data);
                                QJsonObject author_j_obj = author_doc.object();

                                //author's name
                                get_author = author_j_obj["name"].toString();

                                //for multiple authors
                                if(multi_authors){
                                    get_author += "et al.";
                                }
                            }

                            callback(get_title, get_author);
                            //delete later puts in on a stack where Qt will eventually delete it
                            author_reply->deleteLater();
                        });

                        reply->deleteLater();
                        return;
                    }
                }
            }
        }
        //Couldnt GET names so we make them unknown
        callback(get_title, get_author);
        reply->deleteLater();
    });
}

void Text::fetch_book_info(const QString &workId){
    get_book_info(workId, [this](const QString& get_title, const QString& get_author)
    {
        //assign values
        this->book_title = get_title;
        this->book_author = get_author;

        for (int i = 0; i < text_items.size(); i++) {
            if (i == 1) {  // This is the book title text item (second item in your array)
                text_items[i].text = get_title;
            }
            else if (i == 3) {  // This is the author text item (fourth item in your array)
                text_items[i].text = get_author;
            }
        }

        update();
    });
}

void Text::add_text(const QString& text, QFont& font, const QColor& color, int &x, int &y, int width, bool wrap){
    text_items.append(text_items_strc(text,font,color, QPoint(x,y), width, wrap));
    update();
}

void Text::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QString imagePath = "../images/Books.png";

    if (!QFile::exists(imagePath)) {
        qDebug() << "Image file does not exist at path:" << imagePath;
    } else {
        QPixmap backgroundImage(imagePath);
        if (backgroundImage.isNull()) {
            qDebug() << "Failed to load image even though file exists";
        } else {
            painter.drawPixmap(rect(), backgroundImage, backgroundImage.rect());
        }
    }

    for(const text_items_strc& item : text_items) {
        painter.setFont(item.font);
        painter.setPen(item.color);

        if(item.is_word_wrap && item.width > 0) {
            QRect rect(item.pos.x(), item.pos.y(), item.width, 1000/*Height*/);
            painter.drawText(rect, Qt::TextWordWrap, item.text);
        } else {
            painter.drawText(item.pos, item.text);
        }
    }
}