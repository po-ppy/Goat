set names utf8;
use goatdb;
#羊舍数据表中插入数据
insert into houseInfo(houseId) values('舍1');
insert into houseInfo(houseId) values('舍2');
insert into houseInfo(houseId) values('舍3');
insert into houseInfo(houseId) values('舍4');
insert into houseInfo(houseId) values('舍5');
insert into houseInfo(houseId) values('舍6');
#在奶山羊数据表中插入某些数据
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍1',12.3,now(),now());
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍2',42.3,now(),now());
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍3',82.5,now(),now());
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍4',19.3,now(),now());
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍6',12.3,now(),now());
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍5',43.8,now(),now());
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍3',45.3,now(),now());
insert into goatInfo(nickName,houseId,weight,inTime,outTime) values('喜洋洋','舍4',72.9,now(),now());

#在设备信息表中插入数据
insert into deviceInfo(deviceState,inTime) values('闲置',now());
insert into deviceInfo(deviceState,inTime) values('闲置',now());
insert into deviceInfo(deviceState,inTime) values('闲置',now());
insert into deviceInfo(deviceState,inTime) values('闲置',now());
insert into deviceInfo(deviceState,inTime) values('闲置',now());
insert into deviceInfo(deviceState,inTime) values('闲置',now());
insert into deviceInfo(deviceState,inTime) values('闲置',now());

#在绑定信息表中插入数据
#insert into bindingInfo(goatId,deviceId) values(1,1);
#insert into bindingInfo(goatId,deviceId) values(2,2);
#insert into bindingInfo(goatId,deviceId) values(3,3);
#insert into bindingInfo(goatId,deviceId) values(4,4);
#insert into bindingInfo(goatId,deviceId) values(5,5);
#insert into bindingInfo(goatId,deviceId) values(6,6);

insert into bindingInfo(goatId,deviceId) values(1,1) on duplicate key update goatId = values(goatId),deviceId = values(deviceId);
insert into bindingInfo(goatId,deviceId) values(2,2) on duplicate key update goatId = values(goatId),deviceId = values(deviceId);
insert into bindingInfo(goatId,deviceId) values(3,3) on duplicate key update goatId = values(goatId),deviceId = values(deviceId);
insert into bindingInfo(goatId,deviceId) values(4,4) on duplicate key update goatId = values(goatId),deviceId = values(deviceId);
insert into bindingInfo(goatId,deviceId) values(5,5) on duplicate key update goatId = values(goatId),deviceId = values(deviceId);
insert into bindingInfo(goatId,deviceId) values(6,6) on duplicate key update goatId = values(goatId),deviceId = values(deviceId);
