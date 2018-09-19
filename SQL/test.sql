#select a.goatId as 奶山羊编号,a.nickName as 昵称,ifnull(b.deviceId ,'无') as 绑定设备id,a.houseId as 舍号,a.inTime as 入圈时间 from goatInfo a left join bindingInfo c on a.goatId = c.goatId left join deviceInfo b on b.deviceId = c.deviceId where b.deviceId is NULL;
update deviceInfo set deviceState = '故障' where deviceId = 1;
