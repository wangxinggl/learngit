Begin Transaction;
Drop Table If Exists [ChannelInfo];
CREATE TABLE "ChannelInfo"(
[SlaveDevId] integer PRIMARY KEY UNIQUE NOT NULL
,[DevId] integer NOT NULL CONSTRAINT fk_DevInfo_id REFERENCES DevInfo(Id) ON DELETE CASCADE
,[Channel] int NOT NULL
,[ChannelName] varchar(256) NOT NULL
,[Type] int NOT NULL
,[Status] 
  
);
Drop Table If Exists [CommonCfg];
CREATE TABLE [CommonCfg](
[Id] integer PRIMARY KEY UNIQUE NOT NULL
,[PicPath] varchar(256)
,[VideoPath] varchar(256)
,[DownPath] varchar(256)
,[TVWallV] int
,[TVWallH] int
  
);
Drop Table If Exists [DevGroup];
CREATE TABLE "DevGroup"(
[Id] integer PRIMARY KEY UNIQUE
,[GroupId] integer NOT NULL CONSTRAINT fk_UserDevGroup_id REFERENCES UserDevGroup(Id) ON DELETE CASCADE
,[SlaveDevId] int NOT NULL
  
);
Drop Table If Exists [DevInfo];
CREATE TABLE "DevInfo"(
[DevId] integer PRIMARY KEY UNIQUE NOT NULL
,[IpAddr] varchar(64) NOT NULL
,[Port] int NOT NULL
,[LoginName] varchar(64) NOT NULL
,[Password] varchar(64) NOT NULL
,[DevName] varchar(256) UNIQUE NOT NULL
,[Type] int NOT NULL
,[Manufacturer] int NOT NULL
,[DevType] varchar(64) NOT NULL
,[DevStatus] int
  
);
Drop Table If Exists [PresetPos];
CREATE TABLE "PresetPos"(
[Id] integer PRIMARY KEY UNIQUE NOT NULL
,[SlaveDevId] integer NOT NULL
,[PresetNo] integer NOT NULL
,[PresetDesc] varchar(256)
  
);
Drop Table If Exists [TrackPos];
CREATE TABLE "TrackPos"(
[Id] integer PRIMARY KEY NOT NULL
,[TrackSeq] integer NOT NULL
,[PresetPos] integer NOT NULL
,[StayTime] integer NOT NULL
  
);
Drop Table If Exists [TrackSequence];
CREATE TABLE "TrackSequence"(
[Id] integer PRIMARY KEY UNIQUE NOT NULL
,[SlaveDevId] integer NOT NULL
,[TrackNo] integer NOT NULL
,[TrackDesc] varchar(256)
  
);
Drop Table If Exists [TvWallBind];
CREATE TABLE "TvWallBind"(
[Id] integer PRIMARY KEY
,[X] int
,[Y] int
,[DevId] int
,[OutputId] 
,[X2] int
,[Y2] int
  
);
Drop Table If Exists [UserDevGroup];
CREATE TABLE "UserDevGroup"(
[Id] integer PRIMARY KEY UNIQUE NOT NULL
,[GroupName] varchar(256) UNIQUE NOT NULL
,[ParentId] int NOT NULL DEFAULT 0
  
);
Drop Table If Exists [UserInfo];
CREATE TABLE "UserInfo"(
[UId] integer PRIMARY KEY UNIQUE
,[UserName] varchar(64) UNIQUE NOT NULL
,[Password] varchar(64) NOT NULL
  
);
Insert  Into [UserInfo] ([UId],[UserName],[Password]) Values("1","admin","e10adc3949ba59abbe56e057f20f883e");
Drop Table If Exists [VideoPatrol];
CREATE TABLE "VideoPatrol"(
[Id] integer PRIMARY KEY UNIQUE NOT NULL
,[WinIndex] int NOT NULL
,[SlaveDevId] integer NOT NULL
,[StayTime] int NOT NULL
  
);
Commit Transaction;
