TEMPLATE = lib

QT -= gui

TARGET = geos

VER_MAJ = 3
VER_MIN = 4
VER_PAT = 2
VERSION = 3.4.2

INCLUDEPATH += include/

QMAKE_CXXFLAGS += -ffloat-store -fvisibility=hidden -fvisibility-inlines-hidden

CONFIG += object_parallel_to_source c++11

DEFINES += GEOS_INLINE GEOS_DLL_EXPORT

HEADERS += \
    include/geos/algorithm/distance/DiscreteHausdorffDistance.h \
    include/geos/algorithm/distance/DistanceToPoint.h \
    include/geos/algorithm/distance/PointPairDistance.h \
    include/geos/algorithm/locate/IndexedPointInAreaLocator.h \
    include/geos/algorithm/locate/PointOnGeometryLocator.h \
    include/geos/algorithm/locate/SimplePointInAreaLocator.h \
    include/geos/algorithm/Angle.h \
    include/geos/algorithm/BoundaryNodeRule.h \
    include/geos/algorithm/CentralEndpointIntersector.h \
    include/geos/algorithm/Centroid.h \
    include/geos/algorithm/CentroidArea.h \
    include/geos/algorithm/CentroidLine.h \
    include/geos/algorithm/CentroidPoint.h \
    include/geos/algorithm/CGAlgorithms.h \
    include/geos/algorithm/ConvexHull.h \
    include/geos/algorithm/HCoordinate.h \
    include/geos/algorithm/InteriorPointArea.h \
    include/geos/algorithm/InteriorPointLine.h \
    include/geos/algorithm/InteriorPointPoint.h \
    include/geos/algorithm/LineIntersector.h \
    include/geos/algorithm/MCPointInRing.h \
    include/geos/algorithm/MinimumDiameter.h \
    include/geos/algorithm/NotRepresentableException.h \
    include/geos/algorithm/PointInRing.h \
    include/geos/algorithm/PointLocator.h \
    include/geos/algorithm/RayCrossingCounter.h \
    include/geos/algorithm/RobustDeterminant.h \
    include/geos/algorithm/SimplePointInRing.h \
    include/geos/algorithm/SIRtreePointInRing.h \
    include/geos/geom/prep/AbstractPreparedPolygonContains.h \
    include/geos/geom/prep/BasicPreparedGeometry.h \
    include/geos/geom/prep/PreparedGeometry.h \
    include/geos/geom/prep/PreparedGeometryFactory.h \
    include/geos/geom/prep/PreparedLineString.h \
    include/geos/geom/prep/PreparedLineStringIntersects.h \
    include/geos/geom/prep/PreparedPoint.h \
    include/geos/geom/prep/PreparedPolygon.h \
    include/geos/geom/prep/PreparedPolygonContains.h \
    include/geos/geom/prep/PreparedPolygonContainsProperly.h \
    include/geos/geom/prep/PreparedPolygonCovers.h \
    include/geos/geom/prep/PreparedPolygonIntersects.h \
    include/geos/geom/prep/PreparedPolygonPredicate.h \
    include/geos/geom/util/ComponentCoordinateExtracter.h \
    include/geos/geom/util/CoordinateOperation.h \
    include/geos/geom/util/GeometryCombiner.h \
    include/geos/geom/util/GeometryEditor.h \
    include/geos/geom/util/GeometryEditorOperation.h \
    include/geos/geom/util/GeometryExtracter.h \
    include/geos/geom/util/GeometryTransformer.h \
    include/geos/geom/util/LinearComponentExtracter.h \
    include/geos/geom/util/PointExtracter.h \
    include/geos/geom/util/PolygonExtracter.h \
    include/geos/geom/util/ShortCircuitedGeometryVisitor.h \
    include/geos/geom/util/SineStarFactory.h \
    include/geos/geom/BinaryOp.h \
    include/geos/geom/Coordinate.h \
    include/geos/geom/CoordinateArraySequence.h \
    include/geos/geom/CoordinateArraySequenceFactory.h \
    include/geos/geom/CoordinateFilter.h \
    include/geos/geom/CoordinateList.h \
    include/geos/geom/CoordinateSequence.h \
    include/geos/geom/CoordinateSequenceFactory.h \
    include/geos/geom/CoordinateSequenceFilter.h \
    include/geos/geom/Dimension.h \
    include/geos/geom/Envelope.h \
    include/geos/geom/Geometry.h \
    include/geos/geom/GeometryCollection.h \
    include/geos/geom/GeometryComponentFilter.h \
    include/geos/geom/GeometryFactory.h \
    include/geos/geom/GeometryFilter.h \
    include/geos/geom/GeometryList.h \
    include/geos/geom/IntersectionMatrix.h \
    include/geos/geom/Lineal.h \
    include/geos/geom/LinearRing.h \
    include/geos/geom/LineSegment.h \
    include/geos/geom/LineString.h \
    include/geos/geom/Location.h \
    include/geos/geom/MultiLineString.h \
    include/geos/geom/MultiPoint.h \
    include/geos/geom/MultiPolygon.h \
    include/geos/geom/Point.h \
    include/geos/geom/Polygon.h \
    include/geos/geom/Polygonal.h \
    include/geos/geom/PrecisionModel.h \
    include/geos/geom/Puntal.h \
    include/geos/geom/Triangle.h \
    include/geos/geomgraph/index/EdgeSetIntersector.h \
    include/geos/geomgraph/index/MonotoneChain.h \
    include/geos/geomgraph/index/MonotoneChainEdge.h \
    include/geos/geomgraph/index/MonotoneChainIndexer.h \
    include/geos/geomgraph/index/SegmentIntersector.h \
    include/geos/geomgraph/index/SimpleEdgeSetIntersector.h \
    include/geos/geomgraph/index/SimpleMCSweepLineIntersector.h \
    include/geos/geomgraph/index/SimpleSweepLineIntersector.h \
    include/geos/geomgraph/index/SweepLineEvent.h \
    include/geos/geomgraph/index/SweepLineEventObj.h \
    include/geos/geomgraph/index/SweepLineSegment.h \
    include/geos/geomgraph/Depth.h \
    include/geos/geomgraph/DirectedEdge.h \
    include/geos/geomgraph/DirectedEdgeStar.h \
    include/geos/geomgraph/Edge.h \
    include/geos/geomgraph/EdgeEnd.h \
    include/geos/geomgraph/EdgeEndStar.h \
    include/geos/geomgraph/EdgeIntersection.h \
    include/geos/geomgraph/EdgeIntersectionList.h \
    include/geos/geomgraph/EdgeList.h \
    include/geos/geomgraph/EdgeNodingValidator.h \
    include/geos/geomgraph/EdgeRing.h \
    include/geos/geomgraph/GeometryGraph.h \
    include/geos/geomgraph/GraphComponent.h \
    include/geos/geomgraph/Label.h \
    include/geos/geomgraph/Node.h \
    include/geos/geomgraph/NodeFactory.h \
    include/geos/geomgraph/NodeMap.h \
    include/geos/geomgraph/PlanarGraph.h \
    include/geos/geomgraph/Position.h \
    include/geos/geomgraph/Quadrant.h \
    include/geos/geomgraph/TopologyLocation.h \
    include/geos/index/bintree/Bintree.h \
    include/geos/index/bintree/Interval.h \
    include/geos/index/bintree/Key.h \
    include/geos/index/bintree/Node.h \
    include/geos/index/bintree/NodeBase.h \
    include/geos/index/bintree/Root.h \
    include/geos/index/chain/MonotoneChain.h \
    include/geos/index/chain/MonotoneChainBuilder.h \
    include/geos/index/chain/MonotoneChainOverlapAction.h \
    include/geos/index/chain/MonotoneChainSelectAction.h \
    include/geos/index/intervalrtree/IntervalRTreeBranchNode.h \
    include/geos/index/intervalrtree/IntervalRTreeLeafNode.h \
    include/geos/index/intervalrtree/IntervalRTreeNode.h \
    include/geos/index/intervalrtree/SortedPackedIntervalRTree.h \
    include/geos/index/quadtree/DoubleBits.h \
    include/geos/index/quadtree/IntervalSize.h \
    include/geos/index/quadtree/Key.h \
    include/geos/index/quadtree/Node.h \
    include/geos/index/quadtree/NodeBase.h \
    include/geos/index/quadtree/Quadtree.h \
    include/geos/index/quadtree/Root.h \
    include/geos/index/strtree/AbstractNode.h \
    include/geos/index/strtree/AbstractSTRtree.h \
    include/geos/index/strtree/Boundable.h \
    include/geos/index/strtree/Interval.h \
    include/geos/index/strtree/ItemBoundable.h \
    include/geos/index/strtree/SIRtree.h \
    include/geos/index/strtree/STRtree.h \
    include/geos/index/sweepline/SweepLineEvent.h \
    include/geos/index/sweepline/SweepLineIndex.h \
    include/geos/index/sweepline/SweepLineInterval.h \
    include/geos/index/sweepline/SweepLineOverlapAction.h \
    include/geos/index/ItemVisitor.h \
    include/geos/index/SpatialIndex.h \
    include/geos/io/ByteOrderDataInStream.h \
    include/geos/io/ByteOrderValues.h \
    include/geos/io/CLocalizer.h \
    include/geos/io/ParseException.h \
    include/geos/io/StringTokenizer.h \
    include/geos/io/WKBConstants.h \
    include/geos/io/WKBReader.h \
    include/geos/io/WKBWriter.h \
    include/geos/io/WKTReader.h \
    include/geos/io/WKTWriter.h \
    include/geos/io/Writer.h \
    include/geos/linearref/ExtractLineByLocation.h \
    include/geos/linearref/LengthIndexedLine.h \
    include/geos/linearref/LengthIndexOfPoint.h \
    include/geos/linearref/LengthLocationMap.h \
    include/geos/linearref/LinearGeometryBuilder.h \
    include/geos/linearref/LinearIterator.h \
    include/geos/linearref/LinearLocation.h \
    include/geos/linearref/LocationIndexedLine.h \
    include/geos/linearref/LocationIndexOfLine.h \
    include/geos/linearref/LocationIndexOfPoint.h \
    include/geos/noding/snapround/HotPixel.h \
    include/geos/noding/snapround/MCIndexPointSnapper.h \
    include/geos/noding/snapround/MCIndexSnapRounder.h \
    include/geos/noding/snapround/SimpleSnapRounder.h \
    include/geos/noding/BasicSegmentString.h \
    include/geos/noding/FastNodingValidator.h \
    include/geos/noding/FastSegmentSetIntersectionFinder.h \
    include/geos/noding/GeometryNoder.h \
    include/geos/noding/IntersectionAdder.h \
    include/geos/noding/IntersectionFinderAdder.h \
    include/geos/noding/IteratedNoder.h \
    include/geos/noding/MCIndexNoder.h \
    include/geos/noding/MCIndexSegmentSetMutualIntersector.h \
    include/geos/noding/NodableSegmentString.h \
    include/geos/noding/NodedSegmentString.h \
    include/geos/noding/Noder.h \
    include/geos/noding/NodingValidator.h \
    include/geos/noding/Octant.h \
    include/geos/noding/OrientedCoordinateArray.h \
    include/geos/noding/ScaledNoder.h \
    include/geos/noding/SegmentIntersectionDetector.h \
    include/geos/noding/SegmentIntersector.h \
    include/geos/noding/SegmentNode.h \
    include/geos/noding/SegmentNodeList.h \
    include/geos/noding/SegmentPointComparator.h \
    include/geos/noding/SegmentSetMutualIntersector.h \
    include/geos/noding/SegmentString.h \
    include/geos/noding/SegmentStringUtil.h \
    include/geos/noding/SimpleNoder.h \
    include/geos/noding/SingleInteriorIntersectionFinder.h \
    include/geos/noding/SinglePassNoder.h \
    include/geos/operation/buffer/BufferBuilder.h \
    include/geos/operation/buffer/BufferInputLineSimplifier.h \
    include/geos/operation/buffer/BufferOp.h \
    include/geos/operation/buffer/BufferParameters.h \
    include/geos/operation/buffer/BufferSubgraph.h \
    include/geos/operation/buffer/OffsetCurveBuilder.h \
    include/geos/operation/buffer/OffsetCurveSetBuilder.h \
    include/geos/operation/buffer/OffsetSegmentGenerator.h \
    include/geos/operation/buffer/OffsetSegmentString.h \
    include/geos/operation/buffer/RightmostEdgeFinder.h \
    include/geos/operation/buffer/SubgraphDepthLocater.h \
    include/geos/operation/distance/ConnectedElementLocationFilter.h \
    include/geos/operation/distance/ConnectedElementPointFilter.h \
    include/geos/operation/distance/DistanceOp.h \
    include/geos/operation/distance/GeometryLocation.h \
    include/geos/operation/linemerge/EdgeString.h \
    include/geos/operation/linemerge/LineMergeDirectedEdge.h \
    include/geos/operation/linemerge/LineMergeEdge.h \
    include/geos/operation/linemerge/LineMergeGraph.h \
    include/geos/operation/linemerge/LineMerger.h \
    include/geos/operation/linemerge/LineSequencer.h \
    include/geos/operation/overlay/snap/GeometrySnapper.h \
    include/geos/operation/overlay/snap/LineStringSnapper.h \
    include/geos/operation/overlay/snap/SnapIfNeededOverlayOp.h \
    include/geos/operation/overlay/snap/SnapOverlayOp.h \
    include/geos/operation/overlay/validate/FuzzyPointLocator.h \
    include/geos/operation/overlay/validate/OffsetPointGenerator.h \
    include/geos/operation/overlay/validate/OverlayResultValidator.h \
    include/geos/operation/overlay/EdgeSetNoder.h \
    include/geos/operation/overlay/ElevationMatrix.h \
    include/geos/operation/overlay/ElevationMatrixCell.h \
    include/geos/operation/overlay/LineBuilder.h \
    include/geos/operation/overlay/MaximalEdgeRing.h \
    include/geos/operation/overlay/MinimalEdgeRing.h \
    include/geos/operation/overlay/OverlayNodeFactory.h \
    include/geos/operation/overlay/OverlayOp.h \
    include/geos/operation/overlay/PointBuilder.h \
    include/geos/operation/overlay/PolygonBuilder.h \
    include/geos/operation/polygonize/EdgeRing.h \
    include/geos/operation/polygonize/PolygonizeDirectedEdge.h \
    include/geos/operation/polygonize/PolygonizeEdge.h \
    include/geos/operation/polygonize/PolygonizeGraph.h \
    include/geos/operation/polygonize/Polygonizer.h \
    include/geos/operation/predicate/RectangleContains.h \
    include/geos/operation/predicate/RectangleIntersects.h \
    include/geos/operation/predicate/SegmentIntersectionTester.h \
    include/geos/operation/relate/EdgeEndBuilder.h \
    include/geos/operation/relate/EdgeEndBundle.h \
    include/geos/operation/relate/EdgeEndBundleStar.h \
    include/geos/operation/relate/RelateComputer.h \
    include/geos/operation/relate/RelateNode.h \
    include/geos/operation/relate/RelateNodeFactory.h \
    include/geos/operation/relate/RelateNodeGraph.h \
    include/geos/operation/relate/RelateOp.h \
    include/geos/operation/sharedpaths/SharedPathsOp.h \
    include/geos/operation/union/CascadedPolygonUnion.h \
    include/geos/operation/union/CascadedUnion.h \
    include/geos/operation/union/GeometryListHolder.h \
    include/geos/operation/union/PointGeometryUnion.h \
    include/geos/operation/union/UnaryUnionOp.h \
    include/geos/operation/valid/ConnectedInteriorTester.h \
    include/geos/operation/valid/ConsistentAreaTester.h \
    include/geos/operation/valid/IsValidOp.h \
    include/geos/operation/valid/QuadtreeNestedRingTester.h \
    include/geos/operation/valid/RepeatedPointTester.h \
    include/geos/operation/valid/SimpleNestedRingTester.h \
    include/geos/operation/valid/SweeplineNestedRingTester.h \
    include/geos/operation/valid/TopologyValidationError.h \
    include/geos/operation/GeometryGraphOperation.h \
    include/geos/operation/IsSimpleOp.h \
    include/geos/planargraph/algorithm/ConnectedSubgraphFinder.h \
    include/geos/planargraph/DirectedEdge.h \
    include/geos/planargraph/DirectedEdgeStar.h \
    include/geos/planargraph/Edge.h \
    include/geos/planargraph/GraphComponent.h \
    include/geos/planargraph/Node.h \
    include/geos/planargraph/NodeMap.h \
    include/geos/planargraph/PlanarGraph.h \
    include/geos/planargraph/Subgraph.h \
    include/geos/precision/CommonBits.h \
    include/geos/precision/CommonBitsOp.h \
    include/geos/precision/CommonBitsRemover.h \
    include/geos/precision/EnhancedPrecisionOp.h \
    include/geos/precision/GeometryPrecisionReducer.h \
    include/geos/precision/PrecisionReducerCoordinateOperation.h \
    include/geos/precision/SimpleGeometryPrecisionReducer.h \
    include/geos/simplify/DouglasPeuckerLineSimplifier.h \
    include/geos/simplify/DouglasPeuckerSimplifier.h \
    include/geos/simplify/LineSegmentIndex.h \
    include/geos/simplify/TaggedLineSegment.h \
    include/geos/simplify/TaggedLinesSimplifier.h \
    include/geos/simplify/TaggedLineString.h \
    include/geos/simplify/TaggedLineStringSimplifier.h \
    include/geos/simplify/TopologyPreservingSimplifier.h \
    include/geos/triangulate/quadedge/LastFoundQuadEdgeLocator.h \
    include/geos/triangulate/quadedge/LocateFailureException.h \
    include/geos/triangulate/quadedge/QuadEdge.h \
    include/geos/triangulate/quadedge/QuadEdgeLocator.h \
    include/geos/triangulate/quadedge/QuadEdgeSubdivision.h \
    include/geos/triangulate/quadedge/TrianglePredicate.h \
    include/geos/triangulate/quadedge/TriangleVisitor.h \
    include/geos/triangulate/quadedge/Vertex.h \
    include/geos/triangulate/DelaunayTriangulationBuilder.h \
    include/geos/triangulate/IncrementalDelaunayTriangulator.h \
    include/geos/util/Assert.h \
    include/geos/util/AssertionFailedException.h \
    include/geos/util/CoordinateArrayFilter.h \
    include/geos/util/GeometricShapeFactory.h \
    include/geos/util/GEOSException.h \
    include/geos/util/IllegalArgumentException.h \
    include/geos/util/IllegalStateException.h \
    include/geos/util/Interrupt.h \
    include/geos/util/Machine.h \
    include/geos/util/math.h \
    include/geos/util/TopologyException.h \
    include/geos/util/UniqueCoordinateArrayFilter.h \
    include/geos/util/UnsupportedOperationException.h \
    include/geos/export.h \
    include/geos/geom.h \
    include/geos/geomgraph.h \
    include/geos/geomgraphindex.h \
    include/geos/geomUtil.h \
    include/geos/geosAlgorithm.h \
    include/geos/indexBintree.h \
    include/geos/indexChain.h \
    include/geos/indexQuadtree.h \
    include/geos/indexStrtree.h \
    include/geos/indexSweepline.h \
    include/geos/inline.h \
    include/geos/io.h \
    include/geos/noding.h \
    include/geos/nodingSnapround.h \
    include/geos/opBuffer.h \
    include/geos/opDistance.h \
    include/geos/operation.h \
    include/geos/opLinemerge.h \
    include/geos/opOverlay.h \
    include/geos/opPolygonize.h \
    include/geos/opPredicate.h \
    include/geos/opRelate.h \
    include/geos/opValid.h \
    include/geos/planargraph.h \
    include/geos/platform.h \
    include/geos/precision.h \
    include/geos/profiler.h \
    include/geos/spatialIndex.h \
    include/geos/timeval.h \
    include/geos/unload.h \
    include/geos/util.h \
    include/geos/version.h \
    include/geos.h \
    src/operation/valid/IndexedNestedRingTester.h

SOURCES += \
    src/algorithm/distance/DiscreteHausdorffDistance.cpp \
    src/algorithm/distance/DistanceToPoint.cpp \
    src/algorithm/locate/IndexedPointInAreaLocator.cpp \
    src/algorithm/locate/PointOnGeometryLocator.cpp \
    src/algorithm/locate/SimplePointInAreaLocator.cpp \
    src/algorithm/Angle.cpp \
    src/algorithm/BoundaryNodeRule.cpp \
    src/algorithm/Centroid.cpp \
    src/algorithm/CentroidArea.cpp \
    src/algorithm/CentroidLine.cpp \
    src/algorithm/CentroidPoint.cpp \
    src/algorithm/CGAlgorithms.cpp \
    src/algorithm/ConvexHull.cpp \
    src/algorithm/HCoordinate.cpp \
    src/algorithm/InteriorPointArea.cpp \
    src/algorithm/InteriorPointLine.cpp \
    src/algorithm/InteriorPointPoint.cpp \
    src/algorithm/LineIntersector.cpp \
    src/algorithm/MCPointInRing.cpp \
    src/algorithm/MinimumDiameter.cpp \
    src/algorithm/NotRepresentableException.cpp \
    src/algorithm/PointLocator.cpp \
    src/algorithm/RayCrossingCounter.cpp \
    src/algorithm/RobustDeterminant.cpp \
    src/algorithm/SimplePointInRing.cpp \
    src/algorithm/SIRtreePointInRing.cpp \
    src/geom/prep/AbstractPreparedPolygonContains.cpp \
    src/geom/prep/BasicPreparedGeometry.cpp \
    src/geom/prep/PreparedGeometry.cpp \
    src/geom/prep/PreparedGeometryFactory.cpp \
    src/geom/prep/PreparedLineString.cpp \
    src/geom/prep/PreparedLineStringIntersects.cpp \
    src/geom/prep/PreparedPoint.cpp \
    src/geom/prep/PreparedPolygon.cpp \
    src/geom/prep/PreparedPolygonContains.cpp \
    src/geom/prep/PreparedPolygonContainsProperly.cpp \
    src/geom/prep/PreparedPolygonCovers.cpp \
    src/geom/prep/PreparedPolygonIntersects.cpp \
    src/geom/prep/PreparedPolygonPredicate.cpp \
    src/geom/util/ComponentCoordinateExtracter.cpp \
    src/geom/util/CoordinateOperation.cpp \
    src/geom/util/GeometryCombiner.cpp \
    src/geom/util/GeometryEditor.cpp \
    src/geom/util/GeometryTransformer.cpp \
    src/geom/util/ShortCircuitedGeometryVisitor.cpp \
    src/geom/util/SineStarFactory.cpp \
    src/geom/Coordinate.cpp \
    src/geom/CoordinateArraySequence.cpp \
    src/geom/CoordinateArraySequenceFactory.cpp \
    src/geom/CoordinateSequence.cpp \
    src/geom/CoordinateSequenceFactory.cpp \
    src/geom/Dimension.cpp \
    src/geom/Envelope.cpp \
    src/geom/Geometry.cpp \
    src/geom/GeometryCollection.cpp \
    src/geom/GeometryComponentFilter.cpp \
    src/geom/GeometryFactory.cpp \
    src/geom/GeometryList.cpp \
    src/geom/IntersectionMatrix.cpp \
    src/geom/LinearRing.cpp \
    src/geom/LineSegment.cpp \
    src/geom/LineString.cpp \
    src/geom/Location.cpp \
    src/geom/MultiLineString.cpp \
    src/geom/MultiPoint.cpp \
    src/geom/MultiPolygon.cpp \
    src/geom/Point.cpp \
    src/geom/Polygon.cpp \
    src/geom/PrecisionModel.cpp \
    src/geom/Triangle.cpp \
    src/geomgraph/index/MonotoneChainEdge.cpp \
    src/geomgraph/index/MonotoneChainIndexer.cpp \
    src/geomgraph/index/SegmentIntersector.cpp \
    src/geomgraph/index/SimpleEdgeSetIntersector.cpp \
    src/geomgraph/index/SimpleMCSweepLineIntersector.cpp \
    src/geomgraph/index/SimpleSweepLineIntersector.cpp \
    src/geomgraph/index/SweepLineEvent.cpp \
    src/geomgraph/index/SweepLineSegment.cpp \
    src/geomgraph/Depth.cpp \
    src/geomgraph/DirectedEdge.cpp \
    src/geomgraph/DirectedEdgeStar.cpp \
    src/geomgraph/Edge.cpp \
    src/geomgraph/EdgeEnd.cpp \
    src/geomgraph/EdgeEndStar.cpp \
    src/geomgraph/EdgeIntersectionList.cpp \
    src/geomgraph/EdgeList.cpp \
    src/geomgraph/EdgeNodingValidator.cpp \
    src/geomgraph/EdgeRing.cpp \
    src/geomgraph/GeometryGraph.cpp \
    src/geomgraph/GraphComponent.cpp \
    src/geomgraph/Label.cpp \
    src/geomgraph/Node.cpp \
    src/geomgraph/NodeFactory.cpp \
    src/geomgraph/NodeMap.cpp \
    src/geomgraph/PlanarGraph.cpp \
    src/geomgraph/Position.cpp \
    src/geomgraph/Quadrant.cpp \
    src/geomgraph/TopologyLocation.cpp \
    src/index/bintree/Bintree.cpp \
    src/index/bintree/Interval.cpp \
    src/index/bintree/Key.cpp \
    src/index/bintree/Node.cpp \
    src/index/bintree/NodeBase.cpp \
    src/index/bintree/Root.cpp \
    src/index/chain/MonotoneChain.cpp \
    src/index/chain/MonotoneChainBuilder.cpp \
    src/index/chain/MonotoneChainOverlapAction.cpp \
    src/index/chain/MonotoneChainSelectAction.cpp \
    src/index/intervalrtree/IntervalRTreeBranchNode.cpp \
    src/index/intervalrtree/IntervalRTreeLeafNode.cpp \
    src/index/intervalrtree/IntervalRTreeNode.cpp \
    src/index/intervalrtree/SortedPackedIntervalRTree.cpp \
    src/index/quadtree/DoubleBits.cpp \
    src/index/quadtree/IntervalSize.cpp \
    src/index/quadtree/Key.cpp \
    src/index/quadtree/Node.cpp \
    src/index/quadtree/NodeBase.cpp \
    src/index/quadtree/Quadtree.cpp \
    src/index/quadtree/Root.cpp \
    src/index/strtree/AbstractNode.cpp \
    src/index/strtree/AbstractSTRtree.cpp \
    src/index/strtree/Interval.cpp \
    src/index/strtree/ItemBoundable.cpp \
    src/index/strtree/SIRtree.cpp \
    src/index/strtree/STRtree.cpp \
    src/index/sweepline/SweepLineEvent.cpp \
    src/index/sweepline/SweepLineIndex.cpp \
    src/index/sweepline/SweepLineInterval.cpp \
    src/io/ByteOrderDataInStream.cpp \
    src/io/ByteOrderValues.cpp \
    src/io/CLocalizer.cpp \
    src/io/ParseException.cpp \
    src/io/StringTokenizer.cpp \
    src/io/Unload.cpp \
    src/io/WKBReader.cpp \
    src/io/WKBWriter.cpp \
    src/io/WKTReader.cpp \
    src/io/WKTWriter.cpp \
    src/io/Writer.cpp \
    src/linearref/ExtractLineByLocation.cpp \
    src/linearref/LengthIndexedLine.cpp \
    src/linearref/LengthIndexOfPoint.cpp \
    src/linearref/LengthLocationMap.cpp \
    src/linearref/LinearGeometryBuilder.cpp \
    src/linearref/LinearIterator.cpp \
    src/linearref/LinearLocation.cpp \
    src/linearref/LocationIndexOfLine.cpp \
    src/linearref/LocationIndexOfPoint.cpp \
    src/noding/snapround/HotPixel.cpp \
    src/noding/snapround/MCIndexPointSnapper.cpp \
    src/noding/snapround/MCIndexSnapRounder.cpp \
    src/noding/snapround/SimpleSnapRounder.cpp \
    src/noding/BasicSegmentString.cpp \
    src/noding/FastNodingValidator.cpp \
    src/noding/FastSegmentSetIntersectionFinder.cpp \
    src/noding/GeometryNoder.cpp \
    src/noding/IntersectionAdder.cpp \
    src/noding/IntersectionFinderAdder.cpp \
    src/noding/IteratedNoder.cpp \
    src/noding/MCIndexNoder.cpp \
    src/noding/MCIndexSegmentSetMutualIntersector.cpp \
    src/noding/NodedSegmentString.cpp \
    src/noding/NodingValidator.cpp \
    src/noding/Octant.cpp \
    src/noding/OrientedCoordinateArray.cpp \
    src/noding/ScaledNoder.cpp \
    src/noding/SegmentIntersectionDetector.cpp \
    src/noding/SegmentNode.cpp \
    src/noding/SegmentNodeList.cpp \
    src/noding/SegmentString.cpp \
    src/noding/SegmentStringUtil.cpp \
    src/noding/SimpleNoder.cpp \
    src/noding/SingleInteriorIntersectionFinder.cpp \
    src/operation/buffer/BufferBuilder.cpp \
    src/operation/buffer/BufferInputLineSimplifier.cpp \
    src/operation/buffer/BufferOp.cpp \
    src/operation/buffer/BufferParameters.cpp \
    src/operation/buffer/BufferSubgraph.cpp \
    src/operation/buffer/OffsetCurveBuilder.cpp \
    src/operation/buffer/OffsetCurveSetBuilder.cpp \
    src/operation/buffer/OffsetSegmentGenerator.cpp \
    src/operation/buffer/RightmostEdgeFinder.cpp \
    src/operation/buffer/SubgraphDepthLocater.cpp \
    src/operation/distance/ConnectedElementLocationFilter.cpp \
    src/operation/distance/ConnectedElementPointFilter.cpp \
    src/operation/distance/DistanceOp.cpp \
    src/operation/distance/GeometryLocation.cpp \
    src/operation/linemerge/EdgeString.cpp \
    src/operation/linemerge/LineMergeDirectedEdge.cpp \
    src/operation/linemerge/LineMergeEdge.cpp \
    src/operation/linemerge/LineMergeGraph.cpp \
    src/operation/linemerge/LineMerger.cpp \
    src/operation/linemerge/LineSequencer.cpp \
    src/operation/overlay/snap/GeometrySnapper.cpp \
    src/operation/overlay/snap/LineStringSnapper.cpp \
    src/operation/overlay/snap/SnapIfNeededOverlayOp.cpp \
    src/operation/overlay/snap/SnapOverlayOp.cpp \
    src/operation/overlay/validate/FuzzyPointLocator.cpp \
    src/operation/overlay/validate/OffsetPointGenerator.cpp \
    src/operation/overlay/validate/OverlayResultValidator.cpp \
    src/operation/overlay/EdgeSetNoder.cpp \
    src/operation/overlay/ElevationMatrix.cpp \
    src/operation/overlay/ElevationMatrixCell.cpp \
    src/operation/overlay/LineBuilder.cpp \
    src/operation/overlay/MaximalEdgeRing.cpp \
    src/operation/overlay/MinimalEdgeRing.cpp \
    src/operation/overlay/OverlayNodeFactory.cpp \
    src/operation/overlay/OverlayOp.cpp \
    src/operation/overlay/PointBuilder.cpp \
    src/operation/overlay/PolygonBuilder.cpp \
    src/operation/polygonize/EdgeRing.cpp \
    src/operation/polygonize/PolygonizeDirectedEdge.cpp \
    src/operation/polygonize/PolygonizeEdge.cpp \
    src/operation/polygonize/PolygonizeGraph.cpp \
    src/operation/polygonize/Polygonizer.cpp \
    src/operation/predicate/RectangleContains.cpp \
    src/operation/predicate/RectangleIntersects.cpp \
    src/operation/predicate/SegmentIntersectionTester.cpp \
    src/operation/relate/EdgeEndBuilder.cpp \
    src/operation/relate/EdgeEndBundle.cpp \
    src/operation/relate/EdgeEndBundleStar.cpp \
    src/operation/relate/RelateComputer.cpp \
    src/operation/relate/RelateNode.cpp \
    src/operation/relate/RelateNodeFactory.cpp \
    src/operation/relate/RelateNodeGraph.cpp \
    src/operation/relate/RelateOp.cpp \
    src/operation/sharedpaths/SharedPathsOp.cpp \
    src/operation/union/CascadedPolygonUnion.cpp \
    src/operation/union/CascadedUnion.cpp \
    src/operation/union/PointGeometryUnion.cpp \
    src/operation/union/UnaryUnionOp.cpp \
    src/operation/valid/ConnectedInteriorTester.cpp \
    src/operation/valid/ConsistentAreaTester.cpp \
    src/operation/valid/IndexedNestedRingTester.cpp \
    src/operation/valid/IsValidOp.cpp \
    src/operation/valid/QuadtreeNestedRingTester.cpp \
    src/operation/valid/RepeatedPointTester.cpp \
    src/operation/valid/SimpleNestedRingTester.cpp \
    src/operation/valid/SweeplineNestedRingTester.cpp \
    src/operation/valid/TopologyValidationError.cpp \
    src/operation/GeometryGraphOperation.cpp \
    src/operation/IsSimpleOp.cpp \
    src/planargraph/algorithm/ConnectedSubgraphFinder.cpp \
    src/planargraph/DirectedEdge.cpp \
    src/planargraph/DirectedEdgeStar.cpp \
    src/planargraph/Edge.cpp \
    src/planargraph/Node.cpp \
    src/planargraph/NodeMap.cpp \
    src/planargraph/PlanarGraph.cpp \
    src/planargraph/Subgraph.cpp \
    src/precision/CommonBits.cpp \
    src/precision/CommonBitsOp.cpp \
    src/precision/CommonBitsRemover.cpp \
    src/precision/EnhancedPrecisionOp.cpp \
    src/precision/GeometryPrecisionReducer.cpp \
    src/precision/PrecisionReducerCoordinateOperation.cpp \
    src/precision/SimpleGeometryPrecisionReducer.cpp \
    src/simplify/DouglasPeuckerLineSimplifier.cpp \
    src/simplify/DouglasPeuckerSimplifier.cpp \
    src/simplify/LineSegmentIndex.cpp \
    src/simplify/TaggedLineSegment.cpp \
    src/simplify/TaggedLinesSimplifier.cpp \
    src/simplify/TaggedLineString.cpp \
    src/simplify/TaggedLineStringSimplifier.cpp \
    src/simplify/TopologyPreservingSimplifier.cpp \
    src/triangulate/quadedge/LastFoundQuadEdgeLocator.cpp \
    src/triangulate/quadedge/LocateFailureException.cpp \
    src/triangulate/quadedge/QuadEdge.cpp \
    src/triangulate/quadedge/QuadEdgeLocator.cpp \
    src/triangulate/quadedge/QuadEdgeSubdivision.cpp \
    src/triangulate/quadedge/TrianglePredicate.cpp \
    src/triangulate/quadedge/TriangleVisitor.cpp \
    src/triangulate/quadedge/Vertex.cpp \
    src/triangulate/DelaunayTriangulationBuilder.cpp \
    src/triangulate/IncrementalDelaunayTriangulator.cpp \
    src/util/Assert.cpp \
    src/util/GeometricShapeFactory.cpp \
    src/util/Interrupt.cpp \
    src/util/math.cpp \
    src/util/Profiler.cpp \
    src/inlines.cpp
