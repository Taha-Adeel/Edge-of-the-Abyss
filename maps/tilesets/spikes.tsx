<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.5" tiledversion="1.7.0" name="spikes" tilewidth="42" tileheight="42" spacing="2" tilecount="4" columns="4">
 <transformations hflip="1" vflip="1" rotate="1" preferuntransformed="1"/>
 <image source="../../assets/spikes.png" width="176" height="44"/>
 <tile id="0">
  <objectgroup draworder="index" id="2">
   <object id="4" name="Spike" type="TriangleBound" x="0" y="42">
    <polygon points="0,0 42,0 21,-41"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="1">
  <objectgroup draworder="index" id="2">
   <object id="1" name="Spike" type="TriangleBound" x="0" y="42">
    <polygon points="0,0 42,0 21,-12"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="2">
  <objectgroup draworder="index" id="2">
   <object id="1" name="Spike" type="TriangleBound" x="10.5" y="42">
    <polygon points="0,0 21,0 10,-21"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="3">
  <objectgroup draworder="index" id="2">
   <object id="3" name="Spike" type="BoxBound" x="0" y="21" width="42" height="21"/>
  </objectgroup>
 </tile>
</tileset>
