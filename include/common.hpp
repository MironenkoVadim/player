#ifndef COMMON_HPP_
#define COMMON_HPP_

#pragma once

#include <QDataStream>

#pragma pack(push, 1)

namespace okti { namespace common {

/// Набор возможных состояний трассы
enum class StatusTarget : quint8
{
	Reset    = 0,             //!< Трасса сброшены
	Tracking = 1,             //!< Трасса сопровождается
	Capture  = 2              //!< Трасса на захвате (ещё не проверин критерий подтверждения)
};


/// Набор возможных классов целей
enum class ClassTarget : quint8
{
	ClassUndefined      = 0,  //!< Не определен
	Tactical_aviation   = 1,  //!< Тактическая авиация
	Strategic_aviation  = 2,  //!< Стратегическая авиация
	GZLA                = 3,  //!< ГЗЛА
	VTA                 = 4,  //!< Военнотранспортная авиация (ВТА)
	Civil_aviation      = 5,  //!< Гражданская авиция (ГА)
	Naval_aviation      = 6,  //!< Морская авиация
	Jammer              = 7,  //!< Помехопостановщик (ПП)
	Training_aircraft   = 8,  //!< Учебно-тренировочная авиация (УТА)
	Air_cruise_missiles = 9,  //!< Крылатые ракеты воздушного базирования
	Sea_cruise_missiles = 10, //!< Крылатые ракеты морского базирования
	AeroCarrier         = 11, //!< АУГ(AeroCarrier)
	Escorts_ship        = 12, //!< АУГ(Escorts_ship)
	PHO                 = 13, //!< АУГ (РНО)
	Drone               = 14, //!< БПЛА
	Sea_targets         = 16, //!< Надводные цели
	DRLOU               = 31, //!< Специальная авиация ДРЛО
	VKP                 = 32, //!< Специальная авиация ВКП
	SR                  = 33, //!< Специальная авиация СР
	Anti_Missile        = 34, //!< ПротивоРакеты
	COUNT
};


enum class CodogramType : quint16
{
	RadarTracksPack = 0x0302, //!< Набор трасс от радара
	AdsbTracksPack  = 0x0305, //!< Набор трасс от АЗН-В
	MrtTracksPack   = 0x0309, //!< Набор трасс от третички
	AcarsTracksPack = 0x0310, //!< Набор трасс от АКАРС
	Undefined       = 0xFFFF  //!< Не определен
};


/**
 * \brief Идентификаторы программ в проекте
 */

enum class Application : quint16
{
	None        = 0x0000,
	Poi         = 0x0001,
	Accumulator = 0x0002,
	Toi         = 0x0004,
	Any         = 0xFFFF
};


inline QDataStream& operator<<( QDataStream& ds, StatusTarget value )
{
	ds << static_cast< typename std::underlying_type< StatusTarget >::type >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, StatusTarget& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< StatusTarget >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, ClassTarget value )
{
	ds << static_cast< typename std::underlying_type< ClassTarget >::type >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ClassTarget& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< ClassTarget >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, CodogramType value )
{
	ds << static_cast< typename std::underlying_type< CodogramType >::type >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, CodogramType& value )
{
	quint16 t { 0 }; ds >> t; value = static_cast< CodogramType >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, Application value )
{
	ds << static_cast< typename std::underlying_type< Application >::type >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Application& value )
{
	quint16 t { 0 }; ds >> t; value = static_cast< Application >( t );
	return ( ds );
}


inline ClassTarget fromString( const QString& target )
{
	ClassTarget result { ClassTarget::ClassUndefined };

	if ( target == "ClassUndefined" ) {
		result = ClassTarget::ClassUndefined;
	}
	if ( target == "Tactical_aviation" ) {
		result = ClassTarget::Tactical_aviation;
	}
	if ( target == "Strategic_aviation" ) {
		result = ClassTarget::Strategic_aviation;
	}
	if ( target == "GZLA" ) {
		result = ClassTarget::GZLA;
	}
	if ( target == "VTA" ) {
		result = ClassTarget::VTA;
	}
	if ( target == "Civil_aviation" ) {
		result = ClassTarget::Civil_aviation;
	}
	if ( target == "Naval_aviation" ) {
		result = ClassTarget::Naval_aviation;
	}
	if ( target == "Jammer" ) {
		result = ClassTarget::Jammer;
	}
	if ( target == "Training_aircraft" ) {
		result = ClassTarget::Training_aircraft;
	}
	if ( target == "Air_cruise_missiles" ) {
		result = ClassTarget::Air_cruise_missiles;
	}
	if ( target == "Sea_cruise_missiles" ) {
		result = ClassTarget::Sea_cruise_missiles;
	}
	if ( target == "AeroCarrier" ) {
		result = ClassTarget::AeroCarrier;
	}
	if ( target == "Escorts_ship" ) {
		result = ClassTarget::Escorts_ship;
	}
	if ( target == "PHO" ) {
		result = ClassTarget::PHO;
	}
	if ( target == "Drone" ) {
		result = ClassTarget::Drone;
	}
	if ( target == "Sea_targets" ) {
		result = ClassTarget::Sea_targets;
	}
	if ( target == "DRLOU" ) {
		result = ClassTarget::DRLOU;
	}
	if ( target == "VKP" ) {
		result = ClassTarget::VKP;
	}
	if ( target == "SR" ) {
		result = ClassTarget::SR;
	}
	if ( target == "Anti_Missile" ) {
		result = ClassTarget::Anti_Missile;
	}
	return( result );
} // fromString


/*!
 * \brief Базовый заголовок пакета, используемый для всех кодограмм
 */
class Header
{
public:

	quint16 count() const { return( m_count ); }
	void setCount( quint16 newCount )    { m_count = newCount; }

	CodogramType type() { return ( m_type ); }

	quint32 size() const { return ( m_size + static_cast< quint32 >( sizeof( Header ) ) ); }
	quint32 dataSize() { return ( m_size ); }
	const char* constData() { return ( reinterpret_cast< const char* >( this + sizeof( Header ) ) ); }

	Application source() const { return( m_source ); }
	void setSource( Application source ) { m_source = source; }

	Application destination() const { return( m_destination ); }
	void setDestination( Application destination ) { m_destination = destination; }

	friend QDataStream &operator<<( QDataStream& out, const Header& _myStruct )
	{
		out << _myStruct.m_type;
		out << _myStruct.m_source;
		out << _myStruct.m_destination;
		out << _myStruct.m_size;
		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, Header& _myStruct )
	{
		in >> _myStruct.m_type;
		in >> _myStruct.m_source;
		in >> _myStruct.m_destination;
		in >> _myStruct.m_size;

		return( in );
	} // >>

	void setType( CodogramType type ) { m_type = type; }
	void setSize( quint32 size )     { m_size = size; }

private:
	quint16      m_count       { 0 };                       //!< Количество трасс в пакете
	CodogramType m_type        { CodogramType::Undefined }; //!< Тип сообщения, следующего за заголовком
	Application  m_source      { Application::Any };        //!< Источник сообщения
	Application  m_destination { Application::Any };        //!< Назначение сообщения
	quint32      m_size        { 0 };                       //!< Размер сообщения, следующего за заголовком
}; // class Header


/*!
 * \brief Координатная информация о трассе
 */
struct StateTarget
{
	float coord_x;        //!< Координата X (на север) (км)
	float coord_y;        //!< Координата Y (на восток) (км)
	float height;         //!< Высота над поверхностью земли (км)
	float bar_height;     //!< Барометрическая высота
	float Vx;             //!< Скорость по оси X (км/с)
	float Vy;             //!< Скорость по оси Y (км/с)
	float Vh;             //!< Вертикальная скорость (км/с)
	float acc_h;          //!< Вертикальное ускорение (км/с^2)
	friend QDataStream &operator<<( QDataStream& out, const StateTarget& _myStruct )
	{
		out << _myStruct.coord_x;
		out << _myStruct.coord_y;
		out << _myStruct.height;
		out << _myStruct.bar_height;
		out << _myStruct.Vx;
		out << _myStruct.Vy;
		out << _myStruct.Vh;
		out << _myStruct.acc_h;
		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, StateTarget& _myStruct )
	{
		in >> _myStruct.coord_x;
		in >> _myStruct.coord_y;
		in >> _myStruct.height;
		in >> _myStruct.bar_height;
		in >> _myStruct.Vx;
		in >> _myStruct.Vy;
		in >> _myStruct.Vh;
		in >> _myStruct.acc_h;

		return( in );
	} // >>
};

// Coord: Координаты ИРИ
struct Coord
{
	QString msg_id;       // Идентификатор входящего сообщения
	quint16 coord_Number; // Условный номер сеанса выхода
	double  coord_Kxs;    // Широта, град
	double  coord_Kyd;    // Долгота, град
	double  coord_Sko;    // СКО, км

	friend QDataStream &operator<<( QDataStream& out, const Coord& _myStruct )
	{
		out << _myStruct.msg_id;
		out << _myStruct.coord_Number;
		out << _myStruct.coord_Kxs;
		out << _myStruct.coord_Kyd;
		out << _myStruct.coord_Sko;
		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, Coord& _myStruct )
	{
		in >> _myStruct.msg_id;
		in >> _myStruct.coord_Number;
		in >> _myStruct.coord_Kxs;
		in >> _myStruct.coord_Kyd;
		in >> _myStruct.coord_Sko;

		return( in );
	} // >>
}; // struct Coord


// PostInfo: Список параметров пеленгования
struct PostInfo
{
	QString msg_id; // Идентификатор входящего сообщения
	quint16 Number; // Условный номер сеанса выхода
	double  Azim;   // Пеленг, град.
	QString Time;   // Дата, время наблюдения
	double  Kxsp;   // Координаты поста
	double  Kydp;   // Координаты поста
	friend QDataStream &operator<<( QDataStream& out, const PostInfo& _myStruct )
	{
		out << _myStruct.msg_id;
		out << _myStruct.Number;
		out << _myStruct.Azim;
		out << _myStruct.Time;
		out << _myStruct.Kxsp;
		out << _myStruct.Kydp;

		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, PostInfo& _myStruct )
	{
		in >> _myStruct.msg_id;
		in >> _myStruct.Number;
		in >> _myStruct.Azim;
		in >> _myStruct.Time;
		in >> _myStruct.Kxsp;
		in >> _myStruct.Kydp;

		return( in );
	} // >>
}; // struct PostInfo


struct ObjAcars
{
	QString msg_id;       // Идентификатор входящего сообщения
	QString iri_Id;       // Идентификатор (номер) ИРИ
	QString iri_Obj;      // Наименование ИРИ
	QString iri_ObjClass; // Вид ВС
	QString iri_ObjName;  // Вид объекта
	QString iri_ObjType;  // Тип объекта
	QString iri_Country;  // Страна
	uint8_t iri_Pgv;      // Признак по принадлежности
	uint8_t iri_Pbo;      // Признак по типу базирования
	QString iri_Time1;    // Дата, время обнаружения
	QString iri_Time2;    // Дата, время последнего подтверждения
	// ICAOData: Блок параметров ICAO
	QString ICAO;         // Код ICAO
	QString IATA;         // Код IATA
	QString FlightNum;    // Номер рейса
	QString Status;       // Тревожный статус
	QString Class;        // Надкласс / класс ЭО
	QString Base;         // Аэродром (порт) базирования
	QString DepPoint;     // Аэродром вылета (порт отплытия)
	QString ArrPoint;     // Аэродром прибытия (порт прибытия)
	QString MMSI;         // MMSI-номер судна
	QString IMO;          // IMO-номер судна
	double  Speed;        // Скорость, км/ч
	double  Course;       // Курс, град
	QString NavStatus;    // Навигационный статус
	QString Port;         // Порт приписки
	QString ArrTime;      // Дата и время прибытия
	QString updateTime;   // Дата и время вставки записи

	friend QDataStream &operator<<( QDataStream& out, const ObjAcars& _myStruct )
	{
		out << _myStruct.msg_id;
		out << _myStruct.iri_Id;
		out << _myStruct.iri_Obj;
		out << _myStruct.iri_ObjClass;
		out << _myStruct.iri_ObjName;
		out << _myStruct.iri_ObjType;
		out << _myStruct.iri_Country;
		out << _myStruct.iri_Pgv;
		out << _myStruct.iri_Pbo;
		out << _myStruct.iri_Time1;
		out << _myStruct.iri_Time2;
		out << _myStruct.ICAO;
		out << _myStruct.IATA;
		out << _myStruct.FlightNum;
		out << _myStruct.Status;
		out << _myStruct.Class;
		out << _myStruct.Base;
		out << _myStruct.DepPoint;
		out << _myStruct.ArrPoint;
		out << _myStruct.MMSI;
		out << _myStruct.IMO;
		out << _myStruct.Speed;
		out << _myStruct.Course;
		out << _myStruct.NavStatus;
		out << _myStruct.Port;
		out << _myStruct.ArrTime;
		out << _myStruct.updateTime;
		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, ObjAcars& _myStruct )
	{
		in >> _myStruct.msg_id;
		in >> _myStruct.iri_Id;
		in >> _myStruct.iri_Obj;
		in >> _myStruct.iri_ObjClass;
		in >> _myStruct.iri_ObjName;
		in >> _myStruct.iri_ObjType;
		in >> _myStruct.iri_Country;
		in >> _myStruct.iri_Pgv;
		in >> _myStruct.iri_Pbo;
		in >> _myStruct.iri_Time1;
		in >> _myStruct.iri_Time2;
		in >> _myStruct.ICAO;
		in >> _myStruct.IATA;
		in >> _myStruct.FlightNum;
		in >> _myStruct.Status;
		in >> _myStruct.Class;
		in >> _myStruct.Base;
		in >> _myStruct.DepPoint;
		in >> _myStruct.ArrPoint;
		in >> _myStruct.MMSI;
		in >> _myStruct.IMO;
		in >> _myStruct.Speed;
		in >> _myStruct.Course;
		in >> _myStruct.NavStatus;
		in >> _myStruct.Port;
		in >> _myStruct.ArrTime;
		in >> _myStruct.updateTime;
		return( in );
	} // >>
}; // struct ObjectAcars


// struct DataAcars
// {
// 	QString                 msg_id;    // Идентификатор входящего сообщения
// 	ObjAcars                obj;       // Информация об объекте
// 	std::vector< PostInfo > post_info; // PostInfo: Список параметров пеленгования
// 	std::vector< Coord >    coord_;    // Coord: Координаты ИРИ

// 	friend QDataStream &operator<<( QDataStream& out, const DataAcars& _myStruct )
// 	{
// 		out << _myStruct.msg_id;
// 		out << _myStruct.obj;
// 		for ( const auto& ps: _myStruct.post_info ) {
// 			out << ps;
// 		}
// 		for ( const auto& c: _myStruct.coord_ ) {
// 			out << c;
// 		}
// 		return( out );
// 	} // <<

// 	friend QDataStream &operator>>( QDataStream& in, DataAcars& _myStruct )
// 	{
// 		in >> _myStruct.msg_id;
// 		in >> _myStruct.obj;
// 		for ( auto p = _myStruct.post_info.begin(); p != _myStruct.post_info.end(); ++p ) {
// 			in >> *p;
// 		}
// 		for ( auto c = _myStruct.coord_.begin(); c != _myStruct.coord_.end(); ++c ) {
// 			in >> *c;
// 		}
// 		return( in );
// 	} // >>
// }; // struct DataAcars


struct DataAcars
{
	bool     imit_target;         //!< Признак тренажной трассы
	float    m_barHeight { 0.0 }; //!< Барометрическая высота
	uint8_t  m_isAnswer { 0 };
	uint8_t  m_isUpdate { 0 };
	uint16_t m_stub     { 0 };
	uint32_t m_id { UINT32_MAX }; //!< Идентификатор цели

	double track_time;            //!< Время формирование трассы (с)
	double capture_time;          //!< Время взятия на захват (с)
	double tracking_time;         //!< Время взятия на сопровождение (с)

	uint32_t     track_number;    //!< Номер трассы
	StateTarget  coord_state;     //!< Координатная информация о трассе
	ClassTarget  rkc;             //!< Класс цели
	StatusTarget track_state;     //!< Статус трассы
	ObjAcars     obj;

	friend QDataStream &operator<<( QDataStream& out, const DataAcars& _myStruct )
	{
		out << _myStruct.imit_target;
		out << _myStruct.m_id;
		out << _myStruct.track_time;
		out << _myStruct.capture_time;
		out << _myStruct.tracking_time;
		out << _myStruct.m_barHeight;
		out << _myStruct.m_isAnswer;
		out << _myStruct.m_isUpdate;
		out << _myStruct.track_number;
		out << _myStruct.coord_state;
		out << _myStruct.m_isUpdate;
		out << _myStruct.rkc;
		out << _myStruct.track_state;

		out << _myStruct.obj;
		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, DataAcars& _myStruct )
	{
		in >> _myStruct.imit_target;
		in >> _myStruct.m_id;
		in >> _myStruct.track_time;
		in >> _myStruct.capture_time;
		in >> _myStruct.tracking_time;
		in >> _myStruct.m_barHeight;
		in >> _myStruct.m_isAnswer;
		in >> _myStruct.m_isUpdate;
		in >> _myStruct.track_number;
		in >> _myStruct.coord_state;
		in >> _myStruct.m_isUpdate;
		in >> _myStruct.rkc;
		in >> _myStruct.track_state;
		in >> _myStruct.obj;
	} // >>
};


class AcarsTracks
{
public:
	friend QDataStream &operator<<( QDataStream& out, const AcarsTracks& _myStruct )
	{
		out << _myStruct.m_header;
		for ( const auto& track: _myStruct.m_vecAcars ) {
			out << track;
		}

		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, AcarsTracks& _myStruct )
	{
		in >> _myStruct.m_header;
		for ( auto vit = _myStruct.m_vecAcars.begin(); vit != _myStruct.m_vecAcars.end(); ++vit ) {
			in >> *vit;
		}
		return( in );
	} // >>

	Header& header() { return( m_header ); }
	std::vector< DataAcars >& tracks() { return ( m_vecAcars ); }

	quint32 size()     { updateSize(); return( m_header.size() ); }
	quint32 dataSize() { updateSize(); return( m_header.dataSize() ); }
	void updateSize()
	{
		quint32 size = sizeof( Header ) + sizeof( DataAcars );
		m_header.setSize( size );
	}

	void setHeader( const Header& newHeader ) { m_header = newHeader; }

private:
	Header                   m_header;
	std::vector< DataAcars > m_vecAcars;
}; // struct AcarsTrack


struct DataKooti
{
	Header     header;
	uint16_t   sector;
	uint16_t   znk;
	uint16_t   ntra;
	uint16_t   navd;
	uint32_t   nairup;
	uint32_t   nairdn;
	uint32_t   nsvaz;
	double     d_km;
	double     az_gr;
	double     vr_mc;
	double     kurs;
	double     r_gr;
	double     r_pr;
	QString    tobvz;
	QString    tpdps;
	QString    tpriv;
	uint16_t   kateg;
	uint16_t   c_prop;
	uint16_t   c_obj;
	uint16_t   xnu_air;
	uint16_t   xlt_fly;
	uint16_t   xgv_av;
	uint16_t   naz;
	uint16_t   c_point;
	QByteArray routerb;
	uint16_t   maneuver;
	uint16_t   detection;
	uint16_t   split;
	uint16_t   gluing;
	uint16_t   group_val;
	uint16_t   merger;
	double     velocity;
	double     veracity;
	double     std_r;
	double     std_b;
	double     std_v;
	double     std_k;
	uint16_t   ntre;
	double     fi;
	double     la;
	double     r_o;
	double     b_o;
	double     vr_o;
	double     fi_o;
	double     la_o;
	double     vr_o_o;

	friend QDataStream &operator<<( QDataStream& out, const DataKooti& _myStruct )
	{
		out << _myStruct.header;
		out << _myStruct.sector;
		out << _myStruct.znk;
		out << _myStruct.ntra;
		out << _myStruct.navd;
		out << _myStruct.nairup;
		out << _myStruct.nairdn;
		out << _myStruct.nsvaz;
		out << _myStruct.d_km;
		out << _myStruct.az_gr;
		out << _myStruct.vr_mc;
		out << _myStruct.kurs;
		out << _myStruct.r_gr;
		out << _myStruct.r_pr;
		out << _myStruct.tobvz;
		out << _myStruct.tpdps;
		out << _myStruct.tpriv;
		out << _myStruct.kateg;
		out << _myStruct.c_prop;
		out << _myStruct.c_obj;
		out << _myStruct.xnu_air;
		out << _myStruct.xlt_fly;
		out << _myStruct.xgv_av;
		out << _myStruct.naz;
		out << _myStruct.c_point;
		out << _myStruct.routerb;
		out << _myStruct.maneuver;
		out << _myStruct.detection;
		out << _myStruct.split;
		out << _myStruct.gluing;
		out << _myStruct.group_val;
		out << _myStruct.merger;
		out << _myStruct.velocity;
		out << _myStruct.veracity;
		out << _myStruct.std_r;
		out << _myStruct.std_b;
		out << _myStruct.std_v;
		out << _myStruct.std_k;
		out << _myStruct.ntre;
		out << _myStruct.fi;
		out << _myStruct.la;
		out << _myStruct.r_o;
		out << _myStruct.b_o;
		out << _myStruct.vr_o;
		out << _myStruct.fi_o;
		out << _myStruct.la_o;
		out << _myStruct.vr_o_o;

		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, DataKooti& _myStruct )
	{
		in >> _myStruct.header;
		in >> _myStruct.sector;
		in >> _myStruct.znk;
		in >> _myStruct.ntra;
		in >> _myStruct.navd;
		in >> _myStruct.nairup;
		in >> _myStruct.nairdn;
		in >> _myStruct.nsvaz;
		in >> _myStruct.d_km;
		in >> _myStruct.az_gr;
		in >> _myStruct.vr_mc;
		in >> _myStruct.kurs;
		in >> _myStruct.r_gr;
		in >> _myStruct.r_pr;
		in >> _myStruct.tobvz;
		in >> _myStruct.tpdps;
		in >> _myStruct.tpriv;
		in >> _myStruct.kateg;
		in >> _myStruct.c_prop;
		in >> _myStruct.c_obj;
		in >> _myStruct.xnu_air;
		in >> _myStruct.xlt_fly;
		in >> _myStruct.xgv_av;
		in >> _myStruct.naz;
		in >> _myStruct.c_point;
		in >> _myStruct.routerb;
		in >> _myStruct.maneuver;
		in >> _myStruct.detection;
		in >> _myStruct.split;
		in >> _myStruct.gluing;
		in >> _myStruct.group_val;
		in >> _myStruct.merger;
		in >> _myStruct.velocity;
		in >> _myStruct.veracity;
		in >> _myStruct.std_r;
		in >> _myStruct.std_b;
		in >> _myStruct.std_v;
		in >> _myStruct.std_k;
		in >> _myStruct.ntre;
		in >> _myStruct.fi;
		in >> _myStruct.la;
		in >> _myStruct.r_o;
		in >> _myStruct.b_o;
		in >> _myStruct.vr_o;
		in >> _myStruct.fi_o;
		in >> _myStruct.la_o;
		in >> _myStruct.vr_o_o;

		return( in );
	} // >>
}; // struct DataKooti


class KootiTracks
{
public:
	friend QDataStream &operator<<( QDataStream& out, const KootiTracks& _myStruct )
	{
		out << _myStruct.m_header;
		for ( const auto& track: _myStruct.m_vecKooti ) {
			out << track;
		}

		return( out );
	} // <<

	friend QDataStream &operator>>( QDataStream& in, KootiTracks& _myStruct )
	{
		in >> _myStruct.m_header;
		_myStruct.m_vecKooti.resize( _myStruct.m_header.count() );
		for ( auto vit = _myStruct.m_vecKooti.begin(); vit != _myStruct.m_vecKooti.end(); ++vit ) {
			in >> *vit;
		}
		return( in );
	} // >>

	Header& header() { return( m_header ); }
	std::vector< DataKooti >& tracks() { return ( m_vecKooti ); }

	quint32 size()     { updateSize(); return( m_header.size() ); }
	quint32 dataSize() { updateSize(); return( m_header.dataSize() ); }
	void updateSize()
	{
		quint32 size = sizeof( Header ) + sizeof( DataKooti );
		m_header.setSize( size );
	}

	void setHeader( const Header& newHeader ) { m_header = newHeader; }
	void setVecKooti( const std::vector< DataKooti >& newVecKooti ){ m_vecKooti = newVecKooti; }

private:
	Header                   m_header;
	std::vector< DataKooti > m_vecKooti;
}; // class KootiTracks


// struct KootiTracks

} // namespace common

} // namespace okti

#pragma pack(pop)

#endif // ifndef COMMON_HPP_
