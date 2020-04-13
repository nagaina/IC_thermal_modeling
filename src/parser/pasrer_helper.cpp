#include "parser_helper.hpp"

#include "../core/layer.hpp"

#include <cstdio>
#include <QFile>

namespace parser
{
#ifdef OS_LINUX
void fopen_s(FILE **f, const char *name, const char *mode) {
    *f = fopen(name, mode);
    return;
}
#endif    
    
ParserHelper::ParserHelper()
{
	m_scanner = std::shared_ptr<CScanner>(new CScanner);
	m_parser = std::shared_ptr<CParser>(new CParser);
}

std::vector<ICnodePtr> ParserHelper::parseFile(const std::string& filePath)
{
	// staff file loading
	std::FILE* fptr;
	fopen_s(&fptr, filePath.c_str(), "r");
	if (fptr == nullptr)
		//exception
		return std::vector<ICnodePtr>();

	std::fseek(fptr, 0, SEEK_END);
	size_t len = std::ftell(fptr);
	std::fseek(fptr, 0, SEEK_SET);
	std::string data(len + 1, '\0');
	std::fread(&data[0], 1, len, fptr);
	fclose(fptr);

	//	parse
	return m_parser->parse(m_scanner->scanTokens(data));
}

Cic* ParserHelper::parseNetlist(const std::string& fn)
{
  if (fn.empty()) {
        return 0;
    }
    QFile file(QString::fromStdString(fn));
    if (!file.open(QFile::ReadOnly)) {
        return 0;
    }

    unsigned maxR = 0, maxC = 0, maxL = 0;

//    using map = std::map<indexs, double>;
//    map temp_map;

    QByteArray data = file.readLine();
    while( !data.isEmpty() ) {
        //Go to the next line
        data = file.readLine();

        //Remove redundant spaces
        data = data.simplified();
        if (data.isEmpty()) {
            break;
        }

        if ( data.startsWith('*') ) {
            continue;
        }

        int idx = data.indexOf("c");
        if ( idx == -1 ) {
            continue;
        }
        idx += 2;

        QString dataStr = QString(data);
        dataStr.insert(idx, '=');
        dataStr = dataStr.remove(' ');
        QList<QString> parts = dataStr.split( '=' );
        QStringList index = parts[1].split("_");
        if (index.back() == "s") {
            continue;
        }
        //assert(index.size() == 4);
        unsigned r = 0, c = 0, l = 0;
		if (index.size() == 1)
			index.push_back("0");
        r = index[0].toUInt();
        c = index[1].toUInt();
        l = 0;
        if (maxR < r) {
            maxR = r;
        }
        if (maxC < c) {
            maxC = c;
        }
        if (maxL < l) {
            maxL = l;
        }
        //            qreal Iidx = parts[1].toDouble();
/*        QString baStr = parts[2];
        qreal temp;
        /// mikro
        if (baStr.endsWith('k')) {
            baStr = baStr.remove('k');
            temp = baStr.toDouble()*1000;
        } else if (baStr.endsWith('m')) {
            baStr = baStr.remove('m');
            temp = baStr.toDouble()*1000/2;
        } else if (baStr.endsWith('u')) {
            baStr = baStr.remove('u');
            temp = baStr.toDouble()*20;
        } else if (baStr.endsWith('n')) {
            baStr = baStr.remove('n');
            temp = baStr.toDouble()/1000;
        } else if(baStr.endsWith('p')) {
            baStr = baStr.remove('p');
            temp = baStr.toDouble()/1000000;
        } else {
            temp = baStr.toDouble();// *1000000;
        }*/
//        temp_map[indexs(r, c, l)] = temp;
//        tempMap.insert(Iidx, temp); TODO
    }

    file.close();

    Cic* ic = new Cic(maxL + 1, maxC + 1, maxR + 1);

/*    for (map::iterator i = temp_map.begin(); i != temp_map.end(); ++i) {
        core::layer* l = ic->get_layer(i->first.level);
        assert(l != 0);
        std::cout<<i->first.row<<std::endl;
        std::cout<<i->first.column<<std::endl;
        l->set_cell_value(i->first.row, i->first.column, i->second);
    }*/
    if (!file.open(QFile::ReadOnly)) {
        return 0;
    }


//    using map = std::map<indexs, double>;
//    map temp_map;

    data = file.readLine();
    while( !data.isEmpty() ) {
        //Go to the next line
        data = file.readLine();

        //Remove redundant spaces
        data = data.simplified();
        if (data.isEmpty()) {
            break;
        }

        if ( data.startsWith('*') ) {
            continue;
        }

        int idx = data.indexOf("c");
        if ( idx == -1 ) {
            continue;
        }
        idx += 2;
		idx = 0;

        QString dataStr = QString(data);
        dataStr.insert(idx, '=');
        dataStr = dataStr.remove(' ');
        QList<QString> parts = dataStr.split( '=' );
        QStringList index = parts[1].split("_");
        if (index.back() == "s") {
            continue;
        }
        //assert(index.size() == 4);
        unsigned r = 0, c = 0, l = 0;
		if (index.size() == 1)
			index.push_back("0");
        r = index[0].toUInt();
        c = index[1].toUInt();
        //l = index[3].toUInt();
        QString baStr = parts[2];
        qreal temp;
        /// mikro
		if (baStr.endsWith('g'))
			baStr = baStr.remove('g');
        if (baStr.endsWith('k')) {
            baStr = baStr.remove('k');
            temp = baStr.toDouble()*1000;
        } else if (baStr.endsWith('m')) {
            baStr = baStr.remove('m');
            temp = baStr.toDouble()*1000/2;
        } else if (baStr.endsWith('u')) {
            baStr = baStr.remove('u');
            temp = baStr.toDouble()*20;
        } else if (baStr.endsWith('n')) {
            baStr = baStr.remove('n');
            temp = baStr.toDouble()/1000;
        } else if(baStr.endsWith('p')) {
            baStr = baStr.remove('p');
            temp = baStr.toDouble()/1000000;
        } else {
            temp = baStr.toDouble();//*1000000;
        }
		CLayer* la = ic->getLayer(l);
        assert(la != 0);
        //std::cout<<r<<std::endl;
        //std::cout<<c<<std::endl;
        la->set_cell_value(c, temp);
//        temp_map[indexs(r, c, l)] = temp;
//        tempMap.insert(Iidx, temp); TODO
    }
    return ic;
//    qreal fmintemp = 0;
//    qreal fmaxtemp = 0;


/*    //Fill tempVector.
    QVector<qreal> tempVector;
    qreal maxTemp = 0;
    qreal minTemp = 1000000000000;
    QMap<int, qreal>::const_iterator i = tempMap.constBegin();
    QMap<int, qreal>::const_iterator iEnd = tempMap.constEnd();
    while (i != iEnd)
    {
        qreal temp = i.value();
        if(temp > maxTemp)
            maxTemp = temp;

        if(temp < minTemp)
            minTemp = temp;
        tempVector.append(temp);
        i+=2;
    }

    mMaxTemp = maxTemp;
    qDebug() << "mMaxTemp ====" << maxTemp << "\n\n";
    qDebug() << "mMinTemp ====" << minTemp << "\n\n";

    QList<QGraphicsItem *> rectItems = pScene->items();
    foreach(QGraphicsItem* grItem, rectItems)
    {
        Node* node = dynamic_cast<Node*>(grItem);
        if(node)
        {
            RectNode* rNode = new RectNode;
            rNode->m_point = node->m_point;
            rNode->m_hight = node->m_hight;
            rNode->m_weight = node->m_weight;
            rNode->m_name = node->m_name;
            rNode->m_power = node->m_power;

            rNode->setPos(rNode->m_point);
            scene->addItem(rNode);
            scene->clearSelection();
            rNode->setSelected(true);

            nodeList.append(rNode);
        }
    }

    QRectF bRect = scene->itemsBoundingRect();
    QPointF distPoint = QPoint(20,20);
    QRectF cbRect(bRect.topLeft()-distPoint, bRect.bottomRight()+distPoint);

    scene->setSceneRect(bRect);

    int itStep = GraphicsScene::GRID_STEP;
    qreal xStart = cbRect.topLeft().x();
    qreal xEnd = cbRect.topRight().x()-itStep;
    qreal yStart = cbRect.topLeft().y();
    qreal yEnd = cbRect.bottomLeft().y()-itStep;

    int tidx = 0;

    qreal factor =( cbRect.height()*cbRect.width())/(itStep*itStep);

    for(qreal x = xStart; x <= xEnd; x += itStep)
    {
        for(qreal y = yStart; y <= yEnd; y += itStep)
        {
            TempNode* tempNode = new TempNode;
            QRectF gridRect(x, y, itStep, itStep);
            tempNode->m_rect = gridRect;

            QColor color;
            //double h = m_power*256;
            qreal theTemp = tempVector[tidx];

            if(mMaxTemp)
            {
                qreal h = theTemp/mMaxTemp * 256;
                color.setHsl(256-h, 240, 140);
                tempNode->m_color = color;
                tempNode->m_temp = theTemp*100/factor;
                tempNode->m_MaxTemp = mMaxTemp;
            }

            scene->addItem(tempNode);
            violList.append(tempNode);

            ++tidx;
        }
    }

    fmintemp = minTemp*100/factor;
    fmaxtemp = maxTemp*100/factor;

    int row = 0;

    qreal temp_diff = (fmaxtemp - fmintemp)/14.0;

    for (qreal pdval = temp_diff+2; pdval <= fmaxtemp; pdval += temp_diff)
    {
        if(pdval== 0)
            continue;
        int pval = pdval;
        qreal dist = fmaxtemp - fmintemp;

        // For dock widget
        QColor theColor;
        qreal theTemp = (pval-fmintemp)/(fmaxtemp-fmintemp) * 256;
        //theColor.setHsl(255-thePower, 255-thePower, 160);
        theColor.setHsl(256-theTemp, 240, 140);

        model->insertRows(row, 1, QModelIndex());

        model->setData(model->index(row, 0, QModelIndex()),
                       theColor, Qt::DecorationRole);
        model->setData(model->index(row, 0, QModelIndex()),
                       pval);

        row++;
    }*/
}
}
